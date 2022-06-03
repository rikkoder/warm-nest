#ifndef COMPLAINTSFORM_H
#define COMPLAINTSFORM_H

#include "connector.h"
#include "utilities.h"
#include <QDialog>

namespace Ui {
    class ComplaintsForm;
}

class ComplaintsForm : public QDialog {
    Q_OBJECT

    Ui::ComplaintsForm *ui;
    Connector *conn;
    void clearErrorLabels();

public:
    explicit ComplaintsForm(Connector *conn, QWidget *parent = nullptr);
    ~ComplaintsForm();
private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // COMPLAINTSFORM_H
