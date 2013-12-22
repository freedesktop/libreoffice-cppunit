#include <cppunit/Exception.h>

#include "QtTestFailure.h"

class QtTestFailurePrivate
{
    typedef CPPUNIT_NS::Test Test;
    typedef CPPUNIT_NS::SourceLine SourceLine;

public:
    QtTestFailurePrivate()
        : _isError(true)
        , _test(NULL)
        , _srcline()
        , _message()
    {}

    QtTestFailurePrivate(Test *failed,
                         const QString &message,
                         const SourceLine &srcline,
                         bool isError)
        : _isError(isError)
        , _test(failed)
        , _srcline(srcline)
        , _message(message)
    {}

    ~QtTestFailurePrivate()
    {}

public:
    bool _isError;
    Test *_test;
    SourceLine _srcline;
    QString _message;
};

QtTestFailure::QtTestFailure()
    : _d(new QtTestFailurePrivate)
{}

QtTestFailure::QtTestFailure(Test *failed,
                             const QString &message,
                             const CppUnit::SourceLine &srcline,
                             bool isError)
    : _d(new QtTestFailurePrivate(failed, message, srcline, isError))
{}

QtTestFailure::QtTestFailure(const QtTestFailure &other)
    : _d(new QtTestFailurePrivate(*other._d.data()))
{}

QtTestFailure::~QtTestFailure()
{}

QtTestFailure &QtTestFailure::operator =(const QtTestFailure &other)
{
    if (this != &other)
    {
        _d.reset(new QtTestFailurePrivate(*other._d.data()));
    }

    return *this;
}

QtTestFailure::SourceLine QtTestFailure::sourceLine() const
{
    return _d->_srcline;
}

QString QtTestFailure::message() const
{
    return _d->_message;
}

QString QtTestFailure::failedTestName() const
{
    if (_d->_test == NULL)
        return QString();

    return QString::fromStdString(_d->_test->getName());
}

bool QtTestFailure::isError() const
{
    return _d->_isError;
}

bool QtTestFailure::isValid() const
{
    return _d->_test != NULL;
}

