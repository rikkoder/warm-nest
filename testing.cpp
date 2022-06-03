#include "testing.h"

void app_testing::tableFiller(std::unique_ptr<sql::Connection> &conn) {
    std::unique_ptr<sql::PreparedStatement> stmnt;
    // clear and fill with random data
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_int_distribution<int> distr(10000000, 99999999);
    std::uniform_int_distribution<long long> pdistr(1000000000ll, 9999999999ll);
    // hostelers table
    stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("DELETE FROM hostelers"));
    stmnt->executeQuery();
    for (int room = 100; room < 125; room++) {
        uint64_t roll = distr(eng);
        std::string name = "";
        int l = rand()%10;
        for (int i=0; i<l; i++) {
            name += 'a'+(rand()%26);
            if (rand()%5 == 0) name += ' ';
        }

        std::string branch = possible_values::branches[rand()%possible_values::no_of_branches];

        uint64_t phone = pdistr(eng);

        std::string email = "";
        l = rand()%7;
        for (int i=0; i<l+1; i++) {
            email += 'a'+(rand()%26);
        }
        email += '@';
        l = rand()%3 + 1;
        for (int i=0; i<l; i++) {
            email += 'a' + (rand()%26);
        }
        email += ".com";

        uint64_t emergency = pdistr(eng);

        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("INSERT INTO hostelers VALUE ("
                                                                                + std::to_string(room) + ", " + std::to_string(roll)
                                                                                + ", " + enquote(name) + ", " + enquote(branch) + ", " + std::to_string(phone)
                                                                                + ", " + enquote(email) + ", " + std::to_string(emergency) + ", NULL)"));
        stmnt->executeQuery();

        // insert into complaint
        std::string category = possible_values::complaint_categories[rand()%possible_values::no_of_complaint_categories];
        std::string complaint = "";
        l = rand()%30;
        for (int i=0; i<l; i++) {
            complaint += 'a'+(rand()%26);
            if (rand()%9 == 0) complaint += ' ';
        }
        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("INSERT INTO complaints "
                                                                                "(date, roll, category, complaint, status, remark)"
                                                                                " VALUE (CURDATE(), " + std::to_string(roll) + ", "
                                                                                + enquote(category) + ", " + enquote(complaint)
                                                                                + ", FALSE, NULL)"));

        stmnt->executeQuery();
    }

    // staffs table
    stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("DELETE FROM staffs"));
    stmnt->executeQuery();
    for (int i=0; i<10; i++) {
        std::string floor_block = std::to_string(rand()%5) + " " + char('A' + rand()%3);

        uint64_t staff_id = distr(eng);

        std::string name = "";
        int l = rand()%10;
        for (int i=0; i<l; i++) {
            name += 'a'+(rand()%26);
            if (rand()%5 == 0) name += ' ';
        }

        std::string designation = possible_values::designations[rand()%possible_values::no_of_branches];
        std::cerr << enquote(designation) << '\n';

        uint64_t phone = pdistr(eng);

        std::string email = "";
        l = rand()%7;
        for (int i=0; i<l+1; i++) {
            email += 'a'+(rand()%26);
        }
        email += '@';
        l = rand()%3 + 1;
        for (int i=0; i<l; i++) {
            email += 'a' + (rand()%26);
        }
        email += ".com";

        stmnt = std::unique_ptr<sql::PreparedStatement> (conn->prepareStatement("INSERT INTO staffs VALUE("
                                                                                + enquote(floor_block) + ", " + std::to_string(staff_id)
                                                                                + ", " + enquote(name) + ", " + enquote(designation) + ", "
                                                                                + std::to_string(phone) + ", " + enquote(email) + ", NULL)"));
        stmnt->executeQuery();
    }
}
