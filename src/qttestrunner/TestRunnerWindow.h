#ifndef TESTRUNNERWINDOW_H
#define TESTRUNNERWINDOW_H

#include <QScopedPointer>
#include <QWidget>

#include <cppunit/Test.h>

/*!
 * \class TestRunnerWindow
 * \brief This class represents the external interface to the test runner dialog
 */
class TestRunnerWindow : public QWidget
{
    Q_OBJECT

    typedef CPPUNIT_NS::Test Test;

public:
    /*!
     * \brief Constructs a new test runner dialog
     * \param rootTest The root test to use
     * \param parent A pointer to a parent QWidget
     * \param flags Window flags controlling the appearance of the dialog
     */
    TestRunnerWindow(Test* rootTest, QWidget* parent = 0, Qt::WindowFlags flags = 0);

    /*!
     * \brief Destructor
     */
    ~TestRunnerWindow();

public slots:
    /*!
     * \brief Runs the registered root test (and all of its child tests)
     *
     * This slot is used by the test runner to _automatically_ start testing once the dialog
     * is displayed.
     */
    void startTesting();

private:
    QScopedPointer<class TestRunnerWindowPrivate> _d;
};

#endif // TESTRUNNERWINDOW_H
