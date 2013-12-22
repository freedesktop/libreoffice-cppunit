#include <cppunit/Exception.h>

#include "TestRunnerWindow.h"
#include "TestRunnerWindowPrivate.h"

TestRunnerWindow::TestRunnerWindow(Test *rootTest, QWidget* parent, Qt::WindowFlags flags)
    : QWidget(parent, flags)
    , _d(new TestRunnerWindowPrivate(rootTest, this))
{}

TestRunnerWindow::~TestRunnerWindow()
{}

void TestRunnerWindow::startTesting()
{
    _d->startTesting();
}
