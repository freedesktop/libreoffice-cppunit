#include <QDesktopServices>
#include <QFile>
#include <QMutex>
#include <QUrl>
#include <cppunit/Exception.h>

#include "TestRunnerWindowPrivate.h"
#include "ui_TestRunnerWindow.h"

namespace {

class QtSynchronizationObject : public CPPUNIT_NS::SynchronizedObject::SynchronizationObject
{
public:
    QtSynchronizationObject()
        : CPPUNIT_NS::SynchronizedObject::SynchronizationObject()
    {}

    ~QtSynchronizationObject()
    {}

    void lock()
    {
        _mutex.lock();
    }

    void unlock()
    {
        _mutex.unlock();
    }

private:
    QMutex _mutex;
};

} // unnamed namespace

//
// TestRunnerWindowPrivate
//

TestRunnerWindowPrivate::TestRunnerWindowPrivate(Test *root, QWidget *parent)
    : QObject(parent)
    , _model(new TestFailureTableModel(parent))
    , _thread(new TestRunnerThread(parent))
    , _browser(new TestBrowser(root, parent))
    , _listener(new QtTestListener(parent))
    , _rootTest(root)
    , _srcfile()
    , _result()
    , _ui(new Ui::TestRunnerWindow)
{
    _ui->setupUi(parent);
    setup();
    updateTestList(_rootTest);
}

TestRunnerWindowPrivate::~TestRunnerWindowPrivate()
{}

void TestRunnerWindowPrivate::setup()
{
    qRegisterMetaType<QtTestFailure>("QtTestFailure");

    connect(_thread, SIGNAL(started()), SLOT(testingStarted()));
    connect(_thread, SIGNAL(finished()), SLOT(testingFinished()));

    connect(_ui->pushButton_Browse, SIGNAL(clicked()), _browser, SLOT(exec()));
    connect(_ui->pushButton_Stop, SIGNAL(clicked()), SLOT(stopTesting()));
    connect(_ui->pushButton_Run, SIGNAL(clicked()), SLOT(startTesting()));
    connect(_ui->pushButton_Close, SIGNAL(clicked()), parent(), SLOT(close()));
    connect(_ui->toolButton_View, SIGNAL(clicked()), SLOT(viewSourceFile()));
    connect(_ui->comboTest, SIGNAL(currentIndexChanged(int)), SLOT(testIndexChanged(int)));

    connect(_ui->failureView, SIGNAL(activated(QModelIndex)),
            SLOT(displayFailureDetail(QModelIndex)));
    connect(_ui->failureView, SIGNAL(clicked(QModelIndex)),
            SLOT(displayFailureDetail(QModelIndex)));
    connect(_browser, SIGNAL(testSelected(Test*)),
            SLOT(updateTestList(Test*)));
    connect(_listener, SIGNAL(testFailed(QtTestFailure)),
            _model, SLOT(addFailure(QtTestFailure)));

    connect(_listener, SIGNAL(testCaseFinished()), SLOT(testCaseFinished()));
    connect(_listener, SIGNAL(testFailed(QtTestFailure)), SLOT(testCaseFailed()));

    _ui->failureView->setModel(_model);
}

void TestRunnerWindowPrivate::startTesting()
{
    int currentIndex = _ui->comboTest->currentIndex();
    Test *testToRun = _ui->comboTest->itemData(currentIndex).value<Test*>();

    if (testToRun == NULL)
        return;

    clearPreviousRun();
    _result.reset(new TestResult(new QtSynchronizationObject));
    _result->addListener(_listener);

    connect(_listener, SIGNAL(testCaseStarted()), SLOT(testingStarted()));
    connect(_listener, SIGNAL(testCaseFinished()), SLOT(testingFinished()));

    _thread->setTestInformation(testToRun, _result.data());
    _thread->start();
}

void TestRunnerWindowPrivate::stopTesting()
{
    if (_thread->isRunning())
    {
        _ui->pushButton_Stop->setText(tr("Stopping"));
        _thread->adviseToStop();
    }
}

void TestRunnerWindowPrivate::testingStarted()
{
    _ui->comboTest->setEnabled(false);
    _ui->pushButton_Browse->setEnabled(false);
    _ui->pushButton_Close->setEnabled(false);
    _ui->pushButton_Run->setEnabled(false);
    _ui->pushButton_Stop->setEnabled(true);
}

void TestRunnerWindowPrivate::testingFinished()
{
    _ui->comboTest->setEnabled(true);
    _ui->pushButton_Browse->setEnabled(true);
    _ui->pushButton_Close->setEnabled(true);
    _ui->pushButton_Run->setEnabled(true);
    _ui->pushButton_Stop->setEnabled(false);

    if (_ui->pushButton_Stop->text() != tr("Stop Test"))
        _ui->pushButton_Stop->setText(tr("Stop Test"));
}

void TestRunnerWindowPrivate::testIndexChanged(int index)
{
    Test *testToRun = _ui->comboTest->itemData(index).value<Test*>();

    setTestCaseCount(testToRun->countTestCases());
    clearPreviousRun();
}

void TestRunnerWindowPrivate::clearPreviousRun()
{
    _model->clear();
    _ui->label_FailureCount->setText("0");
    _ui->label_TestRunCount->setText("0");
    _ui->progressBar_Run->setValue(0);
    _ui->toolButton_View->setEnabled(false);
    clearFailureDetail();
}

void TestRunnerWindowPrivate::setTestCaseCount(int count)
{
    _ui->label_TestCaseCount->setText(QString::number(count));
    _ui->progressBar_Run->setMaximum(count);
}

void TestRunnerWindowPrivate::testCaseFinished()
{
    int val = _ui->progressBar_Run->value() + 1;
    _ui->label_TestRunCount->setText(QString::number(val));
    _ui->progressBar_Run->setValue(val);
}

void TestRunnerWindowPrivate::testCaseFailed()
{
    int val = _ui->label_FailureCount->text().toInt() + 1;
    _ui->label_FailureCount->setText(QString::number(val));
}

void TestRunnerWindowPrivate::clearFailureDetail()
{
    _ui->groupBox_Details->setTitle(tr("Failure detail for: ..."));
    _ui->lineEdit_Location->clear();
    _ui->plainTextEdit_Message->clear();
}

void TestRunnerWindowPrivate::displayFailureDetail(const QModelIndex &index)
{
    QVariant data = _model->data(index, Qt::UserRole);
    QtTestFailure failure = data.value<QtTestFailure>();

    QString title = tr("Failure detail for: ") + failure.failedTestName();
    _ui->groupBox_Details->setTitle(title);

    QString location = QString::fromStdString(failure.sourceLine().fileName());
    bool fileExists = QFile::exists(location);

    if (fileExists && !_ui->toolButton_View->isEnabled())
    {
        _srcfile = location;
        _ui->toolButton_View->setEnabled(true);
    }
    else if(!fileExists && _ui->toolButton_View->isEnabled())
    {
        _ui->toolButton_View->setEnabled(false);
    }

    location += " (" + QString::number(failure.sourceLine().lineNumber()) + ")";
    _ui->lineEdit_Location->setText(location);

    _ui->plainTextEdit_Message->setPlainText(failure.message());
}

void TestRunnerWindowPrivate::updateTestList(Test *test)
{
    QVariant data;
    QString testName = QString::fromStdString(test->getName());

    int duplicateIndex = _ui->comboTest->findText(testName);
    if (duplicateIndex > -1)
        _ui->comboTest->removeItem(duplicateIndex);

    data.setValue(test);
    _ui->comboTest->insertItem(0, testName , data);
    _ui->comboTest->setCurrentIndex(0);
}

void TestRunnerWindowPrivate::viewSourceFile()
{
    if (_srcfile.isEmpty())
        return;

    QUrl location("file:///" + _srcfile);
    QDesktopServices::openUrl(location);
}
