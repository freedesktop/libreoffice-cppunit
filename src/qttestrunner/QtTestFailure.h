#ifndef QTTESTFAILURE_H
#define QTTESTFAILURE_H

#include <QMetaType>
#include <QScopedPointer>
#include <QString>

#include <cppunit/Test.h>
#include <cppunit/SourceLine.h>

/*!
 * \class QtTestFailure
 * \brief This class represents a test failure.
 */
class QtTestFailure
{
    typedef CPPUNIT_NS::Test Test;
    typedef CPPUNIT_NS::SourceLine SourceLine;

public:
    /*!
     * \brief Constructs an invalid QtTestFailure object
     */
    QtTestFailure();

    /*!
     * \brief Constructs a QtTestFailure object from the given parameters
     * \param failed A pointer to the failed test
     * \param message The failure message
     * \param srcline Information about the location of the failure
     * \param isError \c true: the failure was actually an error, \c false: a standard test failure
     */
    QtTestFailure(Test *failed, const QString &message, const SourceLine &srcline, bool isError);

    /*!
     * \brief Copy c'tor
     * \param other The object to copy
     */
    QtTestFailure(const QtTestFailure &other);

    /*!
     * \brief Destructor.
     */
    ~QtTestFailure();

    /*!
     * \brief Returns information about the location of the failure
     * \return Information about the failure location
     */
    SourceLine sourceLine() const;

    /*!
     * \brief Returns the detailed message of the failure
     * \return The detailed failure message
     */
    QString message() const;

    /*!
     * \brief Returns the name of the failed test
     * \return The name of the failed test
     */
    QString failedTestName() const;

    /*!
     * \brief Returns whether the failure actually was an error
     * \return \c true: the failure was an error, \c false: a standard test failure
     */
    bool isError() const;

    /*!
     * \brief Returns whether this failure object is valid
     * \return \c true: The object is valid, \c false: the object is _not_ valid
     */
    bool isValid() const;

    /*!
     * \brief Copy assignment operator
     * \param other The object to copy
     */
    QtTestFailure &operator =(const QtTestFailure &other);

private:
    QScopedPointer<class QtTestFailurePrivate> _d;
};

Q_DECLARE_METATYPE(QtTestFailure)

#endif // QTTESTFAILURE_H
