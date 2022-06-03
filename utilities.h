#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <QMessageBox>

namespace possible_values {
    enum designation {WARDEN, CARE_TAKER, ELECTRICIAN, GUARD};
    enum branch {IT, CSE, ECE, EE, MECH};

    const uint no_of_designations = 4;
    const std::string designations[] = {"Warden", "Care Taker", "Electrician", "Guard"};
    const uint no_of_branches = 5;
    const std::string branches[] = {"IT", "CSE", "ECE", "EE", "MECH"};
    const uint no_of_complaint_categories = 6;
    const std::string complaint_categories[] = {"Water", "Mess", "Hygiene", "Electricity", "Wi-Fi", "Other"};
}

void alert(QString msg);

std::string enquote(QString qs);
std::string enquote(std::string s);

bool invalid_room(QString room);
bool invalid_roll(QString roll);
bool invalid_name(QString name);
bool invalid_branch(QString branch);
bool invalid_phone(QString phone);
bool invalid_email(QString email);
bool invalid_emergency(QString emergency);
bool invalid_remark(QString remark);

bool invalid_floor_block(QString floor_block);
bool invalid_staff_id(QString staff_id);
bool invalid_designation(QString designation);

bool invalid_complaint_id(QString complaint_id);
bool invalid_complaint_category(QString category);
bool invalid_complaint(QString complaint);

#endif // UTILITIES_H
