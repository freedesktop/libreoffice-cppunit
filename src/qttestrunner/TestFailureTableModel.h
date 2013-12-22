#ifndef TESTRUNNERMODEL_H
#define TESTRUNNERMODEL_H

#include <QAbstractTableModel>
#include <QScopedPointer>

#include "QtTestFailure.h"

/*!
 * \class TestFailureTableModel
 * \brief This class represents the data model for the failure list on the TestRunnerWindow
 */
class TestFailureTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_DISABLE_COPY(TestFailureTableModel)

public:
    /*!
     * \brief Constructs a TestRunnerModel object.
     * \param parent A parent QObject
     */
    TestFailureTableModel(QObject *parent = 0);

    /*!
     * \brief Destructor.
     */
    ~TestFailureTableModel();

    /*!
     * \brief Implements QAbstractItemModel::rowCount()
     * \return The number of rows stored in this model
     */
    int rowCount(const QModelIndex &) const;

    /*!
     * \brief Implements QAbstractItemModel::columnCount()
     * \return The number of columns this model provides.
     */
    int columnCount(const QModelIndex &) const;

    /*!
     * \brief Implements QAbstractItemModel::data()
     * \param index The index of the data to retrieve
     * \param role Specifies the role for which to retrieve data
     * \return The data for the given index and role
     */
    QVariant data(const QModelIndex &index, int role) const;

    /*!
     * \brief Reimplemented from QAbstractTableModel::headerData()
     * \param section The index of the section to retrieve information for
     * \param orientation Either Qt::Horizontal or Qt::Vertical
     * \param role The role to retrieve the header data for
     * \return The header data of the given section for the given orientation and role
     *
     * This method actually returns the column names used in the view on the TestRunnerWindow
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /*!
     * \brief Reimplemented from QAbstractTableModel::headerData()
     * \return Always false
     *
     * As for this model setting the header data is not required, this method does nothing
     * except always returning \c false.
     */
    bool setHeaderData(int, Qt::Orientation, const QVariant&, int);

public slots:
    /*!
     * \brief Clears all data in the underlying data store
     *
     * Calling this slot causes all views using this model to be reset.
     */
    void clear();

    /*!
     * \brief Adds a new failure record to the underlying data store
     * \param failure The failure information to add
     */
    void addFailure(const QtTestFailure &failure);

private:
    QScopedPointer<class TestFailureTableModelPrivate> _d;
};

#endif // TESTRUNNERMODEL_H
