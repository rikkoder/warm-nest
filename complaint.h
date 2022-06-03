#ifndef COMPLAINT_H
#define COMPLAINT_H

#include <QString>


class Complaint {
public:
    Complaint(QString roll, QString category, QString complaint, QString remark);
    std::string category, complaint, remark;
    uint64_t roll;
};

#endif // COMPLAINT_H
