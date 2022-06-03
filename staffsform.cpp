#include "staffsform.h"
#include "ui_staffsform.h"

StaffsForm::StaffsForm(Connector *conn, QWidget *parent) : QDialog(parent), ui(new Ui::StaffsForm) {
    ui->setupUi(this);
    ui->floor_block->setFocus();
    this->conn = conn;

    // initialize designation combobox
    ui->designation->addItem("select option");
    for (uint i = 0; i < possible_values::no_of_designations; i++)
        ui->designation->addItem(possible_values::designations[i].c_str());
    // grey out "select option"
    ui->designation->setItemData(0, false, Qt::UserRole - 1);

    // make error labels red
    ui->floor_blockE->setStyleSheet("QLabel {color: red;}");
    ui->staff_idE->setStyleSheet("QLabel {color: red;}");
    ui->nameE->setStyleSheet("QLabel {color: red;}");
    ui->designation->setStyleSheet("QLabel {color: red;}");
    ui->phoneE->setStyleSheet("QLabel {color: red;}");
    ui->emailE->setStyleSheet("QLabel {color: red;}");
    ui->remarkE->setStyleSheet("QLabel {color: red;}");
    clearErrorLabels();
}

StaffsForm::~StaffsForm() {
    delete ui;
}

void StaffsForm::clearErrorLabels() {
    ui->floor_blockE->setText("");
    ui->staff_idE->setText("");
    ui->nameE->setText("");
    ui->designationE->setText("");
    ui->phoneE->setText("");
    ui->emailE->setText("");
    ui->remarkE->setText("");
}

void StaffsForm::on_ok_clicked() {
    clearErrorLabels();

    QString floor_block = ui->floor_block->text();
    QString staff_id = ui->staff_id->text();
    QString name = ui->name->text();
    QString designation = ui->designation->currentText();
    QString phone = ui->phone->text();
    QString email = ui->email->text();
    QString remark = ui->remark->text();

    bool valid = true;

    // validate inputs
    if (invalid_floor_block(floor_block)) {
        valid = false;
        ui->floor_blockE->setText("invalid Floor-Block !");
    } if (invalid_staff_id(staff_id)) {
        valid = false;
        ui->staff_idE->setText("invalid Staff ID !");
    } if (invalid_name(name)) {
        valid = false;
        ui->nameE->setText("invalid name !");
    } if (invalid_designation(designation)) {
        valid = false;
        ui->designationE->setText("invalid designation !");
    } if (invalid_phone(phone)) {
        valid = false;
        ui->phoneE->setText("invalid phone number !");
    } if (invalid_email(email)) {
        valid = false;
        ui->emailE->setText("invalid email address !");
    } if (invalid_remark(remark)) {
        valid = false;
        ui->remarkE->setText("character limit (50) exceeded !");
    } if (valid) {	// insert value
        sqlerr::query_err resp = conn->addStaff(Staff(floor_block, staff_id, name, designation, phone, email, remark));
        if (resp == sqlerr::NOERR)
            this->close();
        else if (resp == sqlerr::DUP_PRI)
            alert("duplicate Staff ID !");
        else if (resp == sqlerr::DUP_PHONE)
            alert("duplicate phone number !");
        else if (resp == sqlerr::DUP_EMAIL)
            alert("duplicate email address !");
        else
            alert("unknown error occurred !");
    }
}


void StaffsForm::on_cancel_clicked() {
    this->close();
}

