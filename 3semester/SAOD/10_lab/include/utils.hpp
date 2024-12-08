#pragma once
#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

std::vector<std::pair<char, float>> generateRussianAlphabet() {
  std::string alphabet = "אבגדהו¸זחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ";
  std::vector<std::pair<char, float>> result;
  for (char c : alphabet) {
    result.emplace_back(c, 0.0f);
  }
  return result;
}
