#include <cppunit/Exception.h>

#include "QtTestListener.h"

QtTestListener::QtTestListener(QObject *parent)
    : QObject(parent)
    , CPPUNIT_NS::TestListener()
{}

QtTestListener::~QtTestListener()
{}

void QtTestListener::startTest(Test * /*test*/)
{
    emit testCaseStarted();
}

void QtTestListener::addFailure(const TestFailure &failure)
{
    emit testFailed(QtTestFailure(failure.failedTest(),
                                  failure.thrownException()->what(),
                                  failure.sourceLine(),
                                  failure.isError()));
}

void QtTestListener::endTest(Test * /*test*/)
{
    emit testCaseFinished();
}
