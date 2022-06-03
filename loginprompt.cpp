#include "loginprompt.h"
#include "ui_loginprompt.h"

#include <QMessageBox>
#include <iostream>

LoginPrompt::LoginPrompt(QWidget *parent) : QDialog(parent), ui(new Ui::LoginPrompt) {
    ui->setupUi(this);

    // making window unresizable
    this->setMaximumSize(this->size());
    this->setMinimumSize(this->size());

    conn = new Connector();

    ui->usrL->setText("Username:");
    ui->usr->setPlaceholderText("enter usernmae..");
    ui->pswdL->setText("Password:");
    ui->pswd->setPlaceholderText("enter password..");
    ui->pswd->setEchoMode(QLineEdit::Password);
    ui->dbL->setText("Hostel:");
    ui->db->setPlaceholderText("enter hostel name..");
}

LoginPrompt::~LoginPrompt() {
    delete ui;
}

void LoginPrompt::on_ok_clicked() 	{
    if (ui->usr->text().toStdString() == "") {
        alert("username can't be empty !!");
    } else if (ui->db->text().toStdString() == "") {
        alert("Hostel Name can't be empty !!");
    } else if (conn->validate(ui->usr->text(), ui->pswd->text(), ui->db->text())) {
        mw = new MainWindow(nullptr, conn);
        mw->show();
        close();
    } else {
        alert("wrong credentials or hostel name !!");
    }
}


void LoginPrompt::on_cancel_clicked() {
    this->close();
}

