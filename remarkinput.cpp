#include "remarkinput.h"
#include "ui_remarkinput.h"

#include "utilities.h"

RemarkInput::RemarkInput(QWidget *parent, QString label) : QDialog(parent), ui(new Ui::RemarkInput) {
    ui->setupUi(this);
    ui->remark->setFocus();
    ui->label->setText(label);
    ui->errorL->setText("");
    ui->errorL->setStyleSheet("QLabel {color: red};");
}

RemarkInput::~RemarkInput() {
    delete ui;
}

QString RemarkInput::getRemark() {
    return this->remark;
}

void RemarkInput::on_ok_clicked() {
    if (invalid_remark(ui->remark->text())) {
        ui->errorL->setText("remark can't exceed 50 characters !");
        return;
    }

    this->remark = ui->remark->text().replace("\"", "\\\"");
    close();
}

void RemarkInput::on_cancel_clicked() {
    close();
}

