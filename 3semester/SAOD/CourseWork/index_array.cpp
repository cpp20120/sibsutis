#include "index_array.hpp"
#include "sort.hpp"
#include "search.hpp"

IndexArray::IndexArray(const std::vector<EmployeeRecord>& records) {
    for (const auto& record : records) {
        indexArray.push_back(&record);
    }
}

void IndexArray::sortByDepartment() {
    Sort::quickSort(indexArray, 0, indexArray.size() - 1);
}

const EmployeeRecord* IndexArray::search(int departmentId, const std::string& fullName) const {
    return Search::binarySearch(indexArray, departmentId, fullName);
}
