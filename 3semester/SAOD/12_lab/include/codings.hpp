#pragma once

#include <vector>
#include <list>
#include <string>

namespace coding {
    struct Table {
        char symbol = 0;
        double probability = 0;
        double q = 0;
        std::list<int> code;
    };

    void shennon(std::vector<Table> &arr);
    void fano(std::vector<Table> &arr);
    void huffman(std::vector<Table> &arr);
    void gilbert_mur(std::vector<Table> &arr);
} // namespace coding
