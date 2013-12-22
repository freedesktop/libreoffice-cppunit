#ifndef TESTBROWSER_H
#define TESTBROWSER_H

#include <QDialog>
#include <QScopedPointer>

#include <cppunit/Test.h>

namespace Ui {
class TestBrowser;
}

class QTreeWidgetItem;

/*!
 * \class TestBrowser
 * \brief A small dialog that displays all registered tests in a hierarchical tree structure
 *
 * When a test is selected from this tree and the selection is confirmed, a pointer to the selected
 * test is signalled to the outside world.
 */
class TestBrowser : public QDialog
{
    Q_OBJECT

    typedef CPPUNIT_NS::Test Test;

public:
    /*!
     * \brief Constructs the test browser dialog
     * \param rootTest The top level test to use for determining all child tests
     * \param parent A pointer to a parent QWidget
     * \param flags Optional window flags controlling the dialog's appearance
     *        (see the QDialog documentation at http://qt-project.org/doc for further details)
     */
    TestBrowser(Test *rootTest, QWidget *parent = 0, Qt::WindowFlags flags = 0);

    /*!
     * \brief Releases all allocated resources
     */
    ~TestBrowser();

signals:
    /*!
     * \brief Signals that a test was selected on the test tree
     */
    void testSelected(Test *);

private:
    void buildTree(Test *test, QTreeWidgetItem *parentItem);

private slots:
    void accept();

private:
    QScopedPointer<class Ui::TestBrowser> _ui;
};

Q_DECLARE_METATYPE(CPPUNIT_NS::Test *)

#endif // TESTBROWSER_H
