#include "complaintsform.h"
#include "ui_complaintsform.h"

ComplaintsForm::ComplaintsForm(Connector *conn, QWidget *parent) : QDialog(parent), ui(new Ui::ComplaintsForm) {
    ui->setupUi(this);
    ui->roll->setFocus();
    this->conn = conn;

    // initialize designation combobox
    ui->category->addItem("select option");
    for (uint i = 0; i < possible_values::no_of_complaint_categories; i++)
        ui->category->addItem(possible_values::complaint_categories[i].c_str());
    // grey out "select option"
    ui->category->setItemData(0, false, Qt::UserRole - 1);

    // make error labels red
    ui->rollE->setStyleSheet("QLabel {color: red;}");
    ui->categoryE->setStyleSheet("QLabel {color: red;}");
    ui->complaintE->setStyleSheet("QLabel {color: red;}");
    ui->remarkE->setStyleSheet("QLabel {color: red;}");
    clearErrorLabels();
}

ComplaintsForm::~ComplaintsForm() {
    delete ui;
}

void ComplaintsForm::clearErrorLabels() {
    ui->rollE->setText("");
    ui->categoryE->setText("");
    ui->complaintE->setText("");
    ui->remarkE->setText("");
}

void ComplaintsForm::on_ok_clicked() {
    clearErrorLabels();

    QString roll = ui->roll->text();
    QString category = ui->category->currentText();
    QString complaint = ui->complaint->text();
    QString remark = ui->remark->text();

    bool valid = true;

    // validate inputs
    if (invalid_roll(roll)) {
        valid = false;
        ui->rollE->setText("invalid roll number !");
    } if (invalid_complaint_category(category)) {
        valid = false;
        ui->categoryE->setText("invalid complaint category !");
    } if (invalid_complaint(complaint)) {
        valid = false;
        ui->complaintE->setText("character limit (50) exceeded !");
    } if (invalid_remark(remark)) {
        valid = false;
        ui->remarkE->setText("character limit (50) exceeded !");
    } if (valid) {	// insert value
        sqlerr::query_err resp = conn->addComplaint(Complaint(roll, category, complaint, remark));
        if (resp == sqlerr::NOERR)
            this->close();
        else if (resp == sqlerr::DUP_PRI)
            alert("duplicate Complaint ID !");
        else
            alert("unknown error occurred !");
    }
}


void ComplaintsForm::on_cancel_clicked() {
    this->close();
}

