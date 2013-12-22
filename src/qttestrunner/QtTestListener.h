#ifndef QTTESTLISTENER_H
#define QTTESTLISTENER_H

#include <QObject>

#include <cppunit/Test.h>
#include <cppunit/TestListener.h>
#include <cppunit/TestFailure.h>

#include "QtTestFailure.h"

/*!
 * \class QtTestListener
 * \brief A specialized Qt based test listener
 *
 * This listener uses the Qt meta object system for propagation of testing states.
 */
class QtTestListener : public QObject, public CPPUNIT_NS::TestListener
{
    Q_OBJECT
    Q_DISABLE_COPY(QtTestListener)

    typedef CPPUNIT_NS::Test Test;
    typedef CPPUNIT_NS::TestFailure TestFailure;

public:
    /*!
     * \brief Constructs a QtTestListener object.
     * \param parent A parent QObject
     */
    QtTestListener(QObject *parent = 0);

    /*!
     * \brief Destructor.
     */
    ~QtTestListener();

signals:
    /*!
     * \brief Signals that a test case is being executed
     */
    void testCaseStarted();

    /*!
     * \brief Signals that a test failed
     * \param failure Contains information about the failed test
     */
    void testFailed(const QtTestFailure &failure);

    /*!
     * \brief Signals that a test case has finished
     */
    void testCaseFinished();

private:
    void startTest(Test *test);
    void addFailure(const TestFailure &failure);
    void endTest(Test *test);
};

#endif  // QTTESTLISTENER_H
