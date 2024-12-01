#include "sort.hpp"
#include <algorithm>

void Sort::quickSort(std::vector<const EmployeeRecord*>& indexArray, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(indexArray, left, right);
        quickSort(indexArray, left, pivotIndex - 1);
        quickSort(indexArray, pivotIndex + 1, right);
    }
}

int Sort::partition(std::vector<const EmployeeRecord*>& indexArray, int left, int right) {
    const EmployeeRecord* pivot = indexArray[right];
    int i = left - 1;

    for (int j = left; j < right; ++j) {
        if (indexArray[j]->departamentId < pivot->departamentId ||
            (indexArray[j]->departamentId == pivot->departamentId &&
                indexArray[j]->fullName < pivot->fullName)) {
            ++i;
            std::swap(indexArray[i], indexArray[j]);
        }
    }

    std::swap(indexArray[i + 1], indexArray[right]);
    return i + 1;
}
