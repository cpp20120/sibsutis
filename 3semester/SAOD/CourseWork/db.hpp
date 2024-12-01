#pragma once 

#include <vector>
#include <string>

struct EmployeeRecord {
    std::string fullName;
    int departamentId;
    std::string position;
    std::string birthDate;
};

class DataBase {
public:
    explicit DataBase(const std::string& filename);
    const std::vector<EmployeeRecord>& getRecords() const;
    void loadFile();
    void saveToFile();

private:
    std::string filename;
    std::vector<EmployeeRecord> records;
};