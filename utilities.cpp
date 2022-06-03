#include "utilities.h"

void alert(QString msg) {
    QMessageBox alert;
    alert.setText(msg);
    alert.exec();
}

std::string enquote(QString qs) {
    return "'" + qs.replace("'", "\'").replace("\"", "\\\"").toStdString() + "'";
}

std::string enquote(std::string s) {
    QString qs = QString(s.c_str());
    return "'" + qs.replace("'", "\'").replace("\"", "\\\"").toStdString() + "'";
}

bool invalid_room(QString room) {
    if (room.length() > 4 || room.length() == 0) return true;
    return false;
}

bool invalid_roll(QString roll) {
    if (!QRegExp("\\d+").exactMatch(roll) || roll.length() != 8) return true;
    return false;
}

bool invalid_name(QString name) {
    if (!QRegExp("^[A-Za-z\\s]+$").exactMatch(name) || name.length() > 20) return true;
    return false;
}

bool invalid_branch(QString branch) {
    for (uint i = 0; i < possible_values::no_of_branches; i++)
        if (branch == possible_values::branches[i].c_str()) return false;
    return true;

//    if (branch.length() > 10 || branch.length() == 0) return true;
//    return false;
}

bool invalid_phone(QString phone) {
    if (!QRegExp("\\d+").exactMatch(phone) || phone.length() != 10) return true;
    return false;
}

bool invalid_email(QString email) {
    if (!QRegExp("^\\w+@[a-zA-Z_]+\\.[a-zA-Z]{2,3}$").exactMatch(email) || email.length() > 20) return true;
    return false;
}

bool invalid_emergency(QString emergency) {
    if (!QRegExp("\\d+").exactMatch(emergency) || emergency.length() != 10) return true;
    return false;
}

bool invalid_remark(QString remark) {
    if (remark.length() > 50) return true;
    return false;
}

bool invalid_floor_block(QString floor_block) {
    if (QRegExp("^\\d-[A-D]$").exactMatch(floor_block)) return false;
    return true;
}

bool invalid_staff_id(QString staff_id) {
    if (!QRegExp("\\d+").exactMatch(staff_id) || staff_id.length() != 8) return true;
    return false;
}

bool invalid_designation(QString designation) {
    for (uint i = 0; i < possible_values::no_of_designations; i++)
        if (designation == possible_values::designations[i].c_str()) return false;
    return true;
}

bool invalid_complaint_id(QString complaint_id) {
    if (QRegExp("\\d+").exactMatch(complaint_id)) return false;
    return true;
}

bool invalid_complaint_category(QString category) {
    for (uint i = 0; i < possible_values::no_of_complaint_categories; i++)
        if (category == possible_values::complaint_categories[i].c_str()) return false;
    return true;
}

bool invalid_complaint(QString complaint) {
    if (complaint.length() > 50) return true;
    return false;
}
