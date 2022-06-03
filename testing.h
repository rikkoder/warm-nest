#ifndef TESTING_H
#define TESTING_H

#include "utilities.h"
#include <mariadb/conncpp.hpp>
#include <random>
#include <cstdlib>
#include <iostream>

namespace app_testing {
    void tableFiller(std::unique_ptr<sql::Connection> &conn);
}

#endif // TESTING_H
