#include "hostelersform.h"
#include "ui_hostelersform.h"

//#include <QRegExp>
//#include <QMessageBox>

#include <iostream>

HostelersForm::HostelersForm(Connector *conn, QWidget *parent) : QDialog(parent), ui(new Ui::HostelersForm) {
    ui->setupUi(this);
    ui->room->setFocus();
    this->conn = conn;

    // initialize branch combobox
    ui->branch->addItem("select option");
    for (uint i = 0; i < possible_values::no_of_branches; i++)
        ui->branch->addItem(possible_values::branches[i].c_str());
    // grey out "select option"
    ui->branch->setItemData(0, false, Qt::UserRole - 1);

    // make error labels red
    ui->roomE->setStyleSheet("QLabel {color: red;}");
    ui->rollE->setStyleSheet("QLabel {color: red;}");
    ui->nameE->setStyleSheet("QLabel {color: red;}");
    ui->branchE->setStyleSheet("QLabel {color: red;}");
    ui->phoneE->setStyleSheet("QLabel {color: red;}");
    ui->emailE->setStyleSheet("QLabel {color: red;}");
    ui->emergencyE->setStyleSheet("QLabel {color: red;}");
    ui->remarkE->setStyleSheet("QLabel {color: red;}");
    clearErrorLabels();
}

HostelersForm::~HostelersForm() {
    delete ui;
}

//Connector* HostelersForm::getConn() {
//    return this->conn;
//}

void HostelersForm::clearErrorLabels() {
    ui->roomE->setText("");
    ui->rollE->setText("");
    ui->nameE->setText("");
    ui->branchE->setText("");
    ui->phoneE->setText("");
    ui->emailE->setText("");
    ui->emergencyE->setText("");
    ui->remarkE->setText("");
}

void HostelersForm::on_ok_clicked() {
    clearErrorLabels();

    QString room = ui->room->text();
    QString roll = ui->roll->text();
    QString name = ui->name->text();
//    QString branch = ui->branch->text();
    // using combobox for branch
    QString branch = ui->branch->currentText();
    QString phone = ui->phone->text();
    QString email = ui->email->text();
    QString emergency = ui->emergency->text();
    QString remark = ui->remark->text();

    bool valid = true;

    // validate inputs
    if (invalid_room(room)) {
        valid = false;
        ui->roomE->setText("invalid room number !");
    } if (invalid_roll(roll)) {
        valid = false;
        ui->rollE->setText("invalid roll nubmer !");
    } if (invalid_name(name)) {
        valid = false;
        ui->nameE->setText("invalid name !");
    } if (invalid_branch(branch)) {
        valid = false;
        ui->branchE->setText("invalid branch name !");
    } if (invalid_phone(phone)) {
        valid = false;
        ui->phoneE->setText("invalid phone number !");
    } if (invalid_email(email)) {
        valid = false;
        ui->emailE->setText("invalid email address !");
    } if (invalid_emergency(emergency)) {
        valid = false;
        ui->emergencyE->setText("invalid emergency contact !");
    } if (invalid_remark(remark)) {
        valid = false;
        ui->remarkE->setText("character limit (50) exceeded !");
    } if (valid) {	// insert value
        sqlerr::query_err resp = conn->addHosteler(Hosteler(room, roll, name, branch, phone, email, emergency, remark));
        if (resp == sqlerr::NOERR)
            this->close();
        else if (resp == sqlerr::DUP_PRI)
            alert("duplicate roll no !");
        else if (resp == sqlerr::DUP_PHONE)
            alert("duplicate phone number !");
        else if (resp == sqlerr::DUP_EMAIL)
            alert("duplicate email address !");
        else
            alert("unknown error occurred !");
    }
}


void HostelersForm::on_cancel_clicked() {
    this->close();
}

