#include "connector.h"
#include "utilities.h"

Connector::Connector() {
    driver = sql::mariadb::get_driver_instance();
}

bool Connector::validate(QString usr, QString pswd, QString db) {
    try {
        url = sql::SQLString("jdbc:mariadb://localhost:3306/" + db.toStdString());
        properties = sql::Properties({{"user", usr.toStdString()}, {"password", pswd.toStdString()}});
        conn = std::unique_ptr<sql::Connection>(driver->connect(url, properties));
    } catch (sql::SQLException e) {
        return false;
    }

    return true;
}

void Connector::initDB() {
    stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("CREATE TABLE IF NOT EXISTS hostelers ("
                                                                            "room VARCHAR(4) NOT NULL, "
                                                                            "roll INT(8) UNSIGNED PRIMARY KEY, "
                                                                            "name VARCHAR(20) NOT NULL, "
                                                                            "branch VARCHAR(10) NOT NULL, "
                                                                            "phone BIGINT UNSIGNED UNIQUE NOT NULL, "
                                                                            "email VARCHAR(20) UNIQUE NOT NULL, "
                                                                            "emergency_contact BIGINT UNSIGNED NOT NULL, "
                                                                            "remark VARCHAR(50))"));

    stmnt->executeQuery();

    stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("CREATE TABLE IF NOT EXISTS staffs ("
                                                                            "floor_block VARCHAR(3) NOT NULL, "
                                                                            "staff_id INT(8) UNSIGNED PRIMARY KEY, "
                                                                            "name VARCHAR(20) NOT NULL, "
                                                                            "designation VARCHAR(15) NOT NULL, "
                                                                            "phone BIGINT UNSIGNED UNIQUE NOT NULL, "
                                                                            "email VARCHAR(20) UNIQUE NOT NULL, "
                                                                            "remark VARCHAR(50))"));

    stmnt->executeQuery();

    stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("CREATE TABLE IF NOT EXISTS complaints ("
                                                                            "complaint_id BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT, "
                                                                            "date DATE NOT NULL, "
                                                                            "roll INT(8) UNSIGNED NOT NULL, "
                                                                            "category VARCHAR(15) NOT NULL, "
                                                                            "complaint VARCHAR(50) NOT NULL, "
                                                                            "status BOOLEAN NOT NULL, "
                                                                            "remark VARCHAR(50))"));

    stmnt->executeQuery();
}

// hostelers table functions
sql::ResultSet* Connector::getAllHostelers() {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM hostelers ORDER BY room");

    return res;
}

sqlerr::query_err Connector::addHosteler(Hosteler h) {
    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("INSERT INTO hostelers VALUE ("
                                            + enquote(h.room) + ", " + std::to_string(h.roll) + ", "
                                            + enquote(h.name) + ", " + enquote(h.branch) + ", " + std::to_string(h.phone)
                                            + ", " + enquote(h.email) + ", " + std::to_string(h.emergency)
                                            + ", " + enquote(h.remark) + ")"));

        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLSyntaxErrorException e) {

        std::string err(e.what());

        if (err.find("PRI") != std::string::npos)
            return sqlerr::DUP_PRI;
        if (err.find("phone") != std::string::npos)
            return sqlerr::DUP_PHONE;
        if (err.find("email") != std::string::npos)
            return sqlerr::DUP_EMAIL;
        else
            return sqlerr::UNKNOWN;
    }
}

sqlerr::query_err Connector::deleteHosteler(uint64_t n, std::string rolls[]) {
    std::string rollsTuple = "( ";
    for (uint64_t i=0; i<n-1; i++) {
        rollsTuple += rolls[i] + ", ";
    }
    rollsTuple += rolls[n-1] + " )";

    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("DELETE FROM hostelers WHERE roll IN " + rollsTuple));
        stmnt->executeQuery();
        // also remove complaints of these hostelers
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("DELETE FROM complaints WHERE roll IN " + rollsTuple));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}

sqlerr::query_err Connector::remarkHosteler(uint64_t n, std::string rolls[], std::string remark) {
    std::string rollsTuple = "( ";
    for (uint64_t i=0; i<n-1; i++) {
        rollsTuple += rolls[i] + ", ";
    }
    rollsTuple += rolls[n-1] + " )";

    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("UPDATE hostelers SET remark = " + enquote(remark) +
                                                                                "WHERE roll IN " + rollsTuple ));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}


// staffs table functions
sql::ResultSet* Connector::getAllStaffs() {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    sql::ResultSet *res = stmnt->executeQuery("SELECT * FROM staffs ORDER BY floor_block");

    return res;
}


sqlerr::query_err Connector::addStaff(Staff s) {
    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("INSERT INTO staffs VALUE ("
                                            + enquote(s.floor_block) + ", " + std::to_string(s.staff_id) + ", "
                                            + enquote(s.name) + ", " + enquote(s.designation) + ", " + std::to_string(s.phone)
                                            + ", " + enquote(s.email) + ", " + enquote(s.remark) + ")"));

        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLSyntaxErrorException e) {

        std::string err(e.what());

        if (err.find("PRI") != std::string::npos)
            return sqlerr::DUP_PRI;
        if (err.find("phone") != std::string::npos)
            return sqlerr::DUP_PHONE;
        if (err.find("email") != std::string::npos)
            return sqlerr::DUP_EMAIL;
        else
            return sqlerr::UNKNOWN;
    }
}


sqlerr::query_err Connector::deleteStaff(uint64_t n, std::string staff_ids[]) {
    std::string staff_idsTuple = "( ";
    for (uint64_t i=0; i<n-1; i++) {
        staff_idsTuple += staff_ids[i] + ", ";
    }
    staff_idsTuple += staff_ids[n-1] + " )";

    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("DELETE FROM staffs WHERE staff_id IN " + staff_idsTuple));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}


sqlerr::query_err Connector::remarkStaff(uint64_t n, std::string staff_ids[], std::string remark) {
    std::string staff_idsTuple = "( ";
    for (uint64_t i=0; i<n-1; i++) {
        staff_idsTuple += staff_ids[i] + ", ";
    }
    staff_idsTuple += staff_ids[n-1] + " )";

    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("UPDATE staffs SET remark = " + enquote(remark) +
                                                                                "WHERE staff_id IN " + staff_idsTuple ));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}


// complaints table functions
sql::ResultSet* Connector::getAllComplaints() {
    std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
    sql::ResultSet *res = stmnt->executeQuery("SELECT "
                                              "c.complaint_id, c.date, c.roll, h.name, h.room, h.phone, c.category, "
                                              "c.complaint, c.status, c.remark FROM complaints as c, hostelers as h "
                                              "where c.roll = h.roll ORDER BY c.complaint_id");

    return res;
}


sqlerr::query_err Connector::addComplaint(Complaint c) {
    try {
        // don't enter complaint_id (auto increment), CURDATE() for todays date, FALSE for status (complaint not resolved yet)
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("INSERT INTO complaints "
                                                                                "(date, roll, category, complaint, status, remark)"
                                                                                " VALUE (CURDATE(), " + std::to_string(c.roll) + ", "
                                                                                + enquote(c.category) + ", " + enquote(c.complaint)
                                                                                + ", FALSE, " + enquote(c.remark) + ")"));

        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLSyntaxErrorException e) {
        std::string err(e.what());

        if (err.find("PRI") != std::string::npos)
            return sqlerr::DUP_PRI;
        else
            return sqlerr::UNKNOWN;
    }
}


sqlerr::query_err Connector::deleteComplaint(uint64_t n, std::string complaint_ids[]) {
    std::string complaint_idsTuple = "( ";
    for (uint64_t i=0; i<n-1; i++) {
        complaint_idsTuple += complaint_ids[i] + ", ";
    }
    complaint_idsTuple += complaint_ids[n-1] + " )";

    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("DELETE FROM complaints WHERE complaint_id IN " + complaint_idsTuple));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}


sqlerr::query_err Connector::remarkComplaint(uint64_t n, std::string complaint_ids[], std::string remark) {
    std::string complaint_idsTuple = "( ";
    for (uint64_t i=0; i<n-1; i++) {
        complaint_idsTuple += complaint_ids[i] + ", ";
    }
    complaint_idsTuple += complaint_ids[n-1] + " )";

    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("UPDATE complaints SET remark = " + enquote(remark) +
                                                                                "WHERE complaint_id IN " + complaint_idsTuple ));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}


sqlerr::query_err Connector::resolveComplaint(uint64_t n, std::string complaint_ids[]) {
    std::string complaint_idsTuple = "( ";
    for (uint64_t i=0; i<n-1; i++) {
        complaint_idsTuple += complaint_ids[i] + ", ";
    }
    complaint_idsTuple += complaint_ids[n-1] + " )";

    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("UPDATE complaints SET status = TRUE "
                                                                                "WHERE complaint_id IN " + complaint_idsTuple ));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}


sqlerr::query_err Connector::deleteResolvedComplaints() {
    try {
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("DELETE FROM complaints WHERE status = TRUE"));
        stmnt->executeQuery();
        return sqlerr::NOERR;
    } catch (sql::SQLException e) {
        return sqlerr::UNKNOWN;
    }
}
