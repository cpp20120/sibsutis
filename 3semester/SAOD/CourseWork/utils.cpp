#include "utils.hpp"
#include <iostream>
#include <Windows.h> 
#undef min
#undef max
#include <conio.h> 
#include <utility>
#include <algorithm>

void Utils::printDatabase(const std::vector<EmployeeRecord>& records, const std::string& encoding, int pageSize) {
    UINT defaultCodePage = GetConsoleOutputCP();

    if (encoding == "CP866") {
        SetConsoleOutputCP(866);
    }

    int totalRecords = records.size();
    int totalPages = (totalRecords + pageSize - 1) / pageSize; 

    for (int page = 0; page < totalPages; ++page) {
        int startIdx = page * pageSize;
        int endIdx = std::min(startIdx + pageSize, totalRecords);

        std::cout << "���� ������ \"�����������\" (�������� " << page + 1 << " �� " << totalPages << "):\n";
        printSeparator();

        for (int i = startIdx; i < endIdx; ++i) {
            const auto& record = records[i];
            std::cout << "���: " << record.fullName << "\n"
                << "����� ������: " << record.departamentId << "\n"
                << "���������: " << record.position << "\n"
                << "���� ��������: " << record.birthDate << "\n";
            printSeparator();
        }

        if (page < totalPages - 1) {
            std::cout << "������� ����� ������� ��� �������� � ��������� ��������...\n";
            _getch();
        }
    }

    SetConsoleOutputCP(defaultCodePage);
}

void Utils::printSeparator() {
    std::cout << std::string(40, '-') << "\n";
}
