#pragma once

#include "db.hpp"
#include <vector>

class IndexArray {
private:
    std::vector<const EmployeeRecord*> indexArray;

public:
    explicit IndexArray(const std::vector<EmployeeRecord>& records);
    void sortByDepartment();
    const EmployeeRecord* search(int departmentId, const std::string& fullName) const;
};

