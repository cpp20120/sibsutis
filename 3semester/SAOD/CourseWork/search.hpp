#pragma once
#include "db.hpp"
#include <vector>

class Search {
public:
    static const EmployeeRecord* binarySearch(const std::vector<const EmployeeRecord*>& indexArray, int departmentId, const std::string& fullName);
};
