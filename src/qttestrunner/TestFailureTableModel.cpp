#include <QObject>
#include <QMap>

#include <cppunit/Exception.h>

#include "TestFailureTableModel.h"

//
// TestFailureTableModelPrivate
//

class TestFailureTableModelPrivate
{
public:
    // Column header enumeration
    enum Column
    {
        ColumnType      = 0,
        ColumnName      = 1,
        ColumnMessage   = 2
    };

    // Convenience type definition
    typedef QMap<Column, QString> ColumnStringMap;

    // C'tor
    TestFailureTableModelPrivate()
        : columnCount(3)
        , failureString(QObject::tr("Failure"))
        , errorString(QObject::tr("Error"))
        , columnStrings()
        , failures()
    {
        // This would be so much easier using C++11... *sigh*
        ColumnStringMap &map = const_cast<ColumnStringMap&>(columnStrings);
        map.insert(ColumnType, QObject::tr("Type"));
        map.insert(ColumnName, QObject::tr("Test name"));
        map.insert(ColumnMessage, QObject::tr("Message"));
    }

public:
    const int columnCount;
    const QString failureString;
    const QString errorString;
    const ColumnStringMap columnStrings;

    QList<QtTestFailure> failures;
};

//
// TestFailureTableModel
//

TestFailureTableModel::TestFailureTableModel(QObject *parent)
    : QAbstractTableModel(parent)
    , _d(new TestFailureTableModelPrivate)
{}

TestFailureTableModel::~TestFailureTableModel()
{}

int TestFailureTableModel::rowCount(const QModelIndex &) const
{
    return _d->failures.size();
}

int TestFailureTableModel::columnCount(const QModelIndex &) const
{
    return _d->columnCount;
}

QVariant TestFailureTableModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        if (role == Qt::DisplayRole)
        {
            QtTestFailure failure = _d->failures.at(index.row());
            switch (index.column())
            {
            case TestFailureTableModelPrivate::ColumnType:
                return failure.isError()
                        ? QVariant(_d->errorString)
                        : QVariant(_d->failureString);
            case TestFailureTableModelPrivate::ColumnName:
                return QVariant(failure.failedTestName());
            case TestFailureTableModelPrivate::ColumnMessage:
                return QVariant(failure.message());
            default:
                break;
            }
        }
        else if (role == Qt::UserRole)
        {
            QVariant data;
            data.setValue(_d->failures.at(index.row()));
            return data;
        }
    }

    return QVariant();
}

QVariant TestFailureTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
        case TestFailureTableModelPrivate::ColumnType:
            return QVariant(_d->columnStrings.value(TestFailureTableModelPrivate::ColumnType));
        case TestFailureTableModelPrivate::ColumnName:
            return QVariant(_d->columnStrings.value(TestFailureTableModelPrivate::ColumnName));
        case TestFailureTableModelPrivate::ColumnMessage:
            return QVariant(_d->columnStrings.value(TestFailureTableModelPrivate::ColumnMessage));
        default:
            break;
        }
    }

    return QVariant();
}

bool TestFailureTableModel::setHeaderData(int, Qt::Orientation, const QVariant &, int)
{
    // Header is fix, nothing to do here
    return false;
}

void TestFailureTableModel::clear()
{
    beginResetModel();
    _d->failures.clear();
    endResetModel();
}

void TestFailureTableModel::addFailure(const QtTestFailure &failure)
{
    if (!failure.isValid())
        return;

    beginInsertRows(QModelIndex(), _d->failures.size(), _d->failures.size());
    insertRow(_d->failures.size(), QModelIndex());
    _d->failures.append(failure);
    endInsertRows();
}
