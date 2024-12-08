#pragma once

#include <vector>

#include "utils.hpp"

namespace coding {
struct Table {
  char symbol;
  float probability;
  std::vector<int> code;
  std::size_t length_code;
};

std::vector<Table> shennon(std::vector<std::pair<char, float>> p);
std::vector<Table> fano(std::vector<std::pair<char, float>> p);
std::vector<Table> huffman(std::vector<std::pair<char, float>> p);
}  // namespace coding
