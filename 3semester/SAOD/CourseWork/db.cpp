#include "db.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

DataBase::DataBase(const std::string& filename) : filename(filename) {}

const std::vector<EmployeeRecord>& DataBase::getRecords() const {
    return records;
}

void DataBase::loadFile() {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    DataBase::records.clear();
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        EmployeeRecord record;
        ss >> record.fullName >> record.departamentId >> record.position >> record.birthDate;
        records.push_back(record);
    }
}

void DataBase::saveToFile() {
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    for (const auto& record : records) {
        file << record.fullName << " " << record.departamentId << " "
            << record.position << " " << record.birthDate << "\n";
    }
}
