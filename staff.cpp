#include "staff.h"

Staff::Staff(QString floor_block, QString staff_id, QString name, QString designation, QString phone, QString email, QString remark) {
    this->floor_block = floor_block.toStdString();
    this->staff_id = staff_id.toULongLong();
    this->name = name.toStdString();
    this->designation = designation.toStdString();
    this->phone = phone.toULongLong();
    this->email = email.toStdString();
    this->remark = remark.toStdString();
}
