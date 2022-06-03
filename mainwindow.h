#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connector.h"
#include <QItemSelection>

namespace tabs {
    enum {HOSTELERS, STAFFS, COMPLAINTS, ABOUT};
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    Ui::MainWindow *ui;
    Connector *conn;
    void initializeHostelersTable();
    void initializeStaffsTable();
    void initializeComplaintsTable();

public:
    MainWindow(QWidget *parent = nullptr, Connector *conn = nullptr);
    bool validateUser(std::string usr, std::string pswd);
    ~MainWindow();

private slots:
    void on_tabWidget_currentChanged(int index);
    void rowsSelected();

    void on_add_hosteler_clicked();
    void on_delete_hosteler_clicked();
    void on_search_hosteler_clicked();
    void on_remark_hosteler_clicked();

    void on_add_staff_clicked();
    void on_delete_staff_clicked();
    void on_search_staff_clicked();
    void on_remark_staff_clicked();

    void on_add_complaint_clicked();
    void on_delete_complaint_clicked();
    void on_remark_complaint_clicked();
    void on_search_complaint_clicked();
    void on_resolve_complaint_clicked();
    void on_deleteResolved_complaint_clicked();
};
#endif // MAINWINDOW_H
