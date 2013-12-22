#ifndef TESTRUNNERWINDOWPRIVATE_H
#define TESTRUNNERWINDOWPRIVATE_H

#include <QScopedPointer>
#include <QWidget>

#include "QtTestFailure.h"
#include "QtTestListener.h"
#include "TestFailureTableModel.h"
#include "TestRunnerThread.h"
#include "TestBrowser.h"

#include <cppunit/Test.h>

namespace Ui {
class TestRunnerWindow;
}

class TestRunnerWindowPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(TestRunnerWindowPrivate)

    typedef CPPUNIT_NS::Test Test;
    typedef CPPUNIT_NS::TestResult TestResult;

public:
    TestRunnerWindowPrivate(Test *root, QWidget *parent);
    ~TestRunnerWindowPrivate();

public slots:
    void startTesting();

private:
    void setup();

private slots:
    void stopTesting();
    void testingStarted();
    void testingFinished();
    void testIndexChanged(int index);
    void clearPreviousRun();
    void setTestCaseCount(int count);
    void testCaseFinished();
    void testCaseFailed();
    void clearFailureDetail();
    void displayFailureDetail(const QModelIndex &index);
    void updateTestList(Test *test);
    void viewSourceFile();

private:
    TestFailureTableModel *_model;
    TestRunnerThread *_thread;
    TestBrowser *_browser;
    QtTestListener *_listener;
    Test *_rootTest;

    QString _srcfile;

    QScopedPointer<TestResult> _result;
    QScopedPointer<Ui::TestRunnerWindow> _ui;
};

#endif // TESTRUNNERWINDOWPRIVATE_H
