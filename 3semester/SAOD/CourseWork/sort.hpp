#pragma once

#include "db.hpp"
#include <vector>

class Sort {
public:
    static void quickSort(std::vector<const EmployeeRecord*>& indexArray, int left, int right);

private:
    static int partition(std::vector<const EmployeeRecord*>& indexArray, int left, int right);
};

