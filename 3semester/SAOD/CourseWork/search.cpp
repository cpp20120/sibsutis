#include "search.hpp"

const EmployeeRecord* Search::binarySearch(const std::vector<const EmployeeRecord*>& indexArray, int departmentId, const std::string& fullName) {
    int left = 0, right = indexArray.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        const EmployeeRecord* record = indexArray[mid];
        if (record->departamentId < departmentId ||
            (record->departamentId == departmentId && record->fullName < fullName)) {
            left = mid + 1;
        }
        else if (record->departamentId > departmentId ||
            (record->departamentId == departmentId && record->fullName > fullName)) {
            right = mid - 1;
        }
        else {
            return record;
        }
    }

    return nullptr;
}
