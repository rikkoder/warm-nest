#include "complaint.h"

Complaint::Complaint(QString roll, QString category, QString complaint, QString remark) {
    this->roll = roll.toULongLong();
    this->category = category.toStdString();
    this->complaint = complaint.toStdString();
    this->remark = remark.toStdString();
}
