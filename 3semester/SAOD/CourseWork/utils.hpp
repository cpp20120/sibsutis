#pragma once


#include <string>
#include <vector>
#include "db.hpp"

namespace Utils {
    std::string trim(const std::string& str);
     void printDatabase(const std::vector<EmployeeRecord>& records, const std::string& encoding, int pageSize);
    void printSeparator();
}

