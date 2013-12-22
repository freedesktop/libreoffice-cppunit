#include <QTreeWidgetItem>
#include <QVariant>

#include <cppunit/Test.h>

#include "TestBrowser.h"
#include "ui_TestBrowser.h"

TestBrowser::TestBrowser(Test *rootTest, QWidget *parent,  Qt::WindowFlags flags)
    : QDialog(parent, flags),
      _ui(new Ui::TestBrowser)
{
    _ui->setupUi(this);
    buildTree(rootTest, NULL);

    _ui->treeWidget->expandAll();
}

TestBrowser::~TestBrowser()
{
    // no need to delete child widgets, Qt does it all for us
}

void TestBrowser::buildTree(Test *test, QTreeWidgetItem *parentItem)
{
    QTreeWidgetItem *item = (parentItem != NULL)
            ? new QTreeWidgetItem(parentItem)
            : new QTreeWidgetItem(_ui->treeWidget);

    QVariant data;
    data.setValue(test);
    item->setData(0, Qt::UserRole, data);
    item->setText(0, QString::fromStdString(test->getName()));

    if (test->getChildTestCount() > 0  ||    // suite with test
         test->countTestCases() == 0)        // empty suite
    {
        for (int index = 0; index < test->getChildTestCount(); ++index)
            buildTree(test->getChildTestAt(index), item);
    }
}

void TestBrowser::accept()
{
    QList<QTreeWidgetItem*> selectedItems = _ui->treeWidget->selectedItems();

    if(!selectedItems.isEmpty())
    {
        QTreeWidgetItem *selected = selectedItems.first();
        QVariant data = selected->data(0, Qt::UserRole);
        emit testSelected(data.value<Test*>());
    }

    QDialog::accept();
}
