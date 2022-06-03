#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "hosteler.h"
#include "staff.h"
#include "complaint.h"
#include <mariadb/conncpp.hpp>

#include "testing.h"

namespace sqlerr {
    enum query_err{NOERR, DUP_PRI, DUP_PHONE, DUP_EMAIL, UNKNOWN};
}

class Connector {
    sql::Driver *driver;
    sql::SQLString url;
    sql::Properties properties;
    std::unique_ptr<sql::PreparedStatement> stmnt;
    std::unique_ptr<sql::Connection> conn;

public:
    Connector();
    bool validate(QString usr, QString pswd, QString db);
    void initDB();

    sql::ResultSet* getAllHostelers();
    sqlerr::query_err addHosteler(Hosteler h);
    sqlerr::query_err deleteHosteler(uint64_t n, std::string rolls[]);
    sqlerr::query_err remarkHosteler(uint64_t n, std::string rolls[], std::string remark);

    sql::ResultSet* getAllStaffs();
    sqlerr::query_err addStaff(Staff s);
    sqlerr::query_err deleteStaff(uint64_t n, std::string staff_ids[]);
    sqlerr::query_err remarkStaff(uint64_t n, std::string staff_ids[], std::string remark);

    sql::ResultSet* getAllComplaints();
    sqlerr::query_err addComplaint(Complaint c);
    sqlerr::query_err deleteComplaint(uint64_t n, std::string complaint_ids[]);
    sqlerr::query_err remarkComplaint(uint64_t n, std::string complaint_ids[], std::string remark);
    sqlerr::query_err resolveComplaint(uint64_t n, std::string compaint_ids[]);
    sqlerr::query_err deleteResolvedComplaints();
};

#endif // CONNECTOR_H
