#ifndef HOSTELER_H
#define HOSTELER_H

#include <QString>


class Hosteler {
public:
    Hosteler(QString room, QString roll, QString name, QString branch, QString phone, QString email, QString emergency, QString remark);
    std::string room, name, branch, email, remark;
    uint64_t roll, phone, emergency;
};

#endif // HOSTELER_H
