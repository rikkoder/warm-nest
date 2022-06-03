#ifndef HOSTELERSFORM_H
#define HOSTELERSFORM_H

#include "connector.h"
#include "utilities.h"
#include "hosteler.h"
#include <QDialog>

namespace Ui {
    class HostelersForm;
}

class HostelersForm : public QDialog {
    Q_OBJECT

    Ui::HostelersForm *ui;
    Connector *conn;
    void clearErrorLabels();

public:
    explicit HostelersForm(Connector *conn, QWidget *parent = nullptr);
    ~HostelersForm();
//    Connector* getConn();

private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // HOSTELERSFORM_H
