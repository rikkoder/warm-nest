#ifndef STAFF_H
#define STAFF_H

#include <QString>


class Staff {
public:
    Staff(QString floor_block, QString staff_id, QString name, QString designation, QString phone, QString email, QString remark);
    std::string floor_block, name, designation, email, remark;
    uint64_t staff_id, phone;
};

#endif // STAFF_H
