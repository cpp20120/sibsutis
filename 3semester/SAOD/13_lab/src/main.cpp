
#include "../include/strstring.hpp"
#include "../include/utils.hpp"

#include <print>
#include <Windows.h>

int main() {
    SetConsoleOutputCP(1251);

    std::string str = "Декабрь - это волшебный месяц, когда границы между реальностью и сказкой стираются, и снег, словно пушистая перина, накрывает землю. С началом зимы начинается время праздников, тепла и уюта, которое хочется запечатлеть не только в сердце, но и в каждом взгляде на экран своего телефона или компьютера.";
    std::string word = "ка";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, str.size() - 1);

    int compares = 0;
    auto indexes = str::strstr(str, word, compares);

    std::println("Text: {}", str);
    std::println("Word: {}", word);
    std::print("\n    Simple Indexes: ");
    for (int index : indexes) std::print("{} ", index);
    std::println("\nCompares: {}\n", compares);

    compares = 0;
    indexes = str::rabin_losos(str, word, compares);
    std::print("Rabin-Karp Indexes: ");
    for (int index : indexes) std::print("{} ", index);
    std::println("\nCompares: {}", compares);
}