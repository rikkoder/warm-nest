#include "hosteler.h"

Hosteler::Hosteler(QString room, QString roll, QString name, QString branch, QString phone, QString email, QString emergency, QString remark) {
    this->room = room.toStdString();
    this->roll = roll.toULongLong();
    this->name = name.toStdString();
    this->branch = branch.toStdString();
    this->phone = phone.toULongLong();
    this->email = email.toStdString();
    this->emergency = emergency.toULongLong();
    this->remark = remark.toStdString();
}
