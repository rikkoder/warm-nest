#ifndef STAFFSFORM_H
#define STAFFSFORM_H

#include "connector.h"
#include "utilities.h"
#include "staff.h"
#include <QDialog>

namespace Ui {
    class StaffsForm;
}

class StaffsForm : public QDialog {
    Q_OBJECT

    Ui::StaffsForm *ui;
    Connector *conn;
    void clearErrorLabels();

public:
    explicit StaffsForm(Connector *conn, QWidget *parent = nullptr);
    ~StaffsForm();
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // 0STAFFSFORM_H
