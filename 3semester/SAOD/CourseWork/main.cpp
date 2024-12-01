#include "db.hpp"
#include "index_array.hpp"
#include "tree.hpp"
#include "utils.hpp"
#include "coding.hpp"
#include <Windows.h>

#include <iostream>

void displayMenu() {
    SetConsoleOutputCP(1251);
    Utils::printSeparator();
    std::cout << "1. Загрузить базу данных из файла\n";
    std::cout << "2. Печать базы данных постранично\n";
    std::cout << "3. Сортировать записи методом Хоара\n";
    std::cout << "4. Поиск записи через индексный массив\n";
    std::cout << "5. Поиск записи через B-дерево\n";
    std::cout << "6. Кодирование записей методом Шеннона\n";
    std::cout << "7. Выход\n";
    Utils::printSeparator();
    std::cout << "Выберите действие: ";
    
}

int main() {
    const std::string filename = "testBase2.dat";
    DataBase db(filename);

    std::string encoding = "CP866"; 
    int pageSize = 100;

    IndexArray* indexArray = nullptr;
    BTree bTree(2); // Порядок дерева B=2

    while (true) {
        displayMenu();

        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
            case 1:
                db.loadFile();
                std::cout << "База данных загружена.\n";
                break;
            case 2:
                SetConsoleOutputCP(866);
                Utils::printDatabase(db.getRecords(), encoding, pageSize);
                SetConsoleOutputCP(1251);
                break;
            
            case 3:
                delete indexArray;
                indexArray = new IndexArray(db.getRecords());
                indexArray->sortByDepartment();
                std::cout << "Записи отсортированы.\n";
                break;
            case 4: {
                if (!indexArray) {
                    std::cout << "Сначала создайте индексный массив.\n";
                    break;
                }
                int deptId;
                std::string name;
                std::cout << "Введите номер отдела: ";
                std::cin >> deptId;
                std::cout << "Введите ФИО: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                SetConsoleOutputCP(866);
                const EmployeeRecord* record = indexArray->search(deptId, name);
                if (record) {
                    std::cout << "Найдено: " << record->fullName << "\n";
                }
                else {
                    std::cout << "Запись не найдена.\n";
                }
                break;
            }
            case 5: {
                for (const auto& record : db.getRecords()) {
                    bTree.insert(&record);
                }

                int deptId;
                std::cout << "Введите номер отдела для поиска: ";
                std::cin >> deptId;

                const EmployeeRecord* record = bTree.search(deptId);
                if (record) {
                    std::cout << "Найдено: " << record->fullName << "\n";
                }
                else {
                    std::cout << "Запись не найдена.\n";
                }
                break;
            }
            case 6: {
                std::string input;
                std::cout << "Введите строку для кодирования: ";
                std::cin.ignore();
                std::getline(std::cin, input);

                auto codes = ShannonCoding::encode(input);
                std::cout << "Кодировка: \n";
                for (const auto& [c, code] : codes) {
                    std::cout << c << ": " << code << "\n";
                }
                break;
            }   
            case 7:
                delete indexArray;
                std::cout << "Выход.\n";
                return 0;
            default:
                std::cout << "Неверный выбор.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }
}
