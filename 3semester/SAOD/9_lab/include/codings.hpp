#pragma once

#include <vector>

#include "utils.hpp"

namespace coding {
struct Table {
  char symbol;
  float probability;
  float q = 0;
  std::vector<int> code;
  std::size_t length_code;
};

std::vector<Table> shennon(std::vector<Table> &p);
}  // namespace coding
