
#include "../include/codings.hpp"
#include "../include/utils.hpp"
#include <Windows.h>

int main() {
    SetConsoleOutputCP(1251);
    std::string file_name = "chars.txt";
    int file_size = 10240;

    std::vector<coding::Table> alphabet = {
        coding::Table({ 'a' }),
        coding::Table({ 'б' }),
        coding::Table({ 'в' }),
        coding::Table({ 'г' }),
        coding::Table({ 'д' }),
        coding::Table({ 'е' }),
        coding::Table({ 'ё' }),
        coding::Table({ 'ж' }),
        coding::Table({ 'з' }),
        coding::Table({ 'и' }),
        coding::Table({ 'й' }),
        coding::Table({ 'к' }),
        coding::Table({ 'л' }),
        coding::Table({ 'м' }),
        coding::Table({ 'н' }),
        coding::Table({ 'о' }),
        coding::Table({ 'п' }),
        coding::Table({ 'р' }),
        coding::Table({ 'с' }),
        coding::Table({ 'т' }),
        coding::Table({ 'у' }),
        coding::Table({ 'ф' }),
        coding::Table({ 'х' }),
        coding::Table({ 'ц' }),
        coding::Table({ 'ч' }),
        coding::Table({ 'ш' }),
        coding::Table({ 'щ' }),
        coding::Table({ 'ъ' }),
        coding::Table({ 'ы' }),
        coding::Table({ 'ь' }),
        coding::Table({ 'э' }),
        coding::Table({ 'ю' }),
        coding::Table({ 'я' })
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::ofstream file_out(file_name);
        for (std::size_t i = 0; i < file_size; ++i) file_out << alphabet.at(dis(gen)).symbol;
        file_out.close();
        file.open(file_name);
    }

    while (!file.eof()) {
        char c = 0;
        file >> c;
        for (coding::Table &symbol : alphabet)
            if (c == symbol.symbol) ++symbol.probability;
    }
    for (coding::Table &symbol : alphabet) symbol.probability /= static_cast<float>(file_size);
    file.close();

    // coding::shennon(alphabet);
    //coding::fano(alphabet); 
     coding::huffman(alphabet); 

    std::size_t max_lentgh = 0;
    for (const coding::Table &table : alphabet)
        if (max_lentgh < table.code.size()) max_lentgh = table.code.size();

    std::println(" Char | Probability |   Code | Length Code");
    for (const coding::Table &table : alphabet) {
        std::print(" {:>4} | {:<11} | ", table.symbol, table.probability);
        if (table.code.size() < max_lentgh)
            for (int i = 0; i < max_lentgh - table.code.size(); ++i) std::print(" ");
        for (const int &i : table.code) std::print("{}", i);
        std::println(" | {}", table.code.size());
    }

    float sum = 0;
    for (const coding::Table &table : alphabet) {
        sum += 1.0f / std::pow(2.0f, table.code.size());
    }
    float ml = 0, entropy = 0;
    for (const coding::Table &table : alphabet) {
        ml += table.probability * table.code.size();
        entropy += table.probability * -std::log2(table.probability);
    }

    std::println("\n Неравенство Крафта |                            Энтропия |    Средняя длинна |         Избыточность");
    std::println("    SUM 1/2^Li <= 1 | H(P1, ..., Pn) = SUM Pi * -log2(Pi) | Lср = SUM Pi * Li | Lср - H(P1, ..., Pn)");
    std::println("{:14f} <= 1 | {:35f} | {:17} | {:20}", sum, ml, entropy, ml - entropy);

    std::print("\nТекст: ");
    std::vector<coding::Table> str(100);
    for (coding::Table &s : str) {
        s = alphabet.at(dis(gen));
        std::print("{}", s.symbol);
    }
    std::print("\nКод: ");
    std::size_t code_size = 0;
    for (coding::Table &s : str) {
        for (auto i : s.code) {
            std::print("{}", i);
            ++code_size;
        }
    }
    std::println("\nРазмер исходной строки: 800\nДлинна кода: {}\nКоэффициент сжатия данных: {}", code_size, static_cast<float>(code_size) / 800.0f);
}