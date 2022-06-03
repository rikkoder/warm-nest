#ifndef LOGINPROMPT_H
#define LOGINPROMPT_H

#include "utilities.h"
#include "connector.h"
#include "mainwindow.h"
#include <QDialog>

namespace Ui {
class LoginPrompt;
}

class LoginPrompt : public QDialog {
    Q_OBJECT

    Ui::LoginPrompt *ui;
    Connector *conn;
    MainWindow *mw;

public:
    explicit LoginPrompt(QWidget *parent = nullptr);
    ~LoginPrompt();

private slots:
    void on_ok_clicked();
    void on_cancel_clicked();
};

#endif // LOGINPROMPT_H
