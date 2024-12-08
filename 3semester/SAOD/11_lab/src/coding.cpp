#include <algorithm>
#include <cmath>

#include "../include/codings.hpp"

inline std::vector<coding::Table> coding::shennon(
    std::vector<std::pair<char, float>> p) {
  std::sort(
      p.begin(), p.end(),
      [](const std::pair<char, float> &a, const std::pair<char, float> &b) {
        return a.second > b.second;
      });
  p.insert(p.begin(), std::pair<char, float>(0, 0.0f));

  auto n = p.size();

  std::vector<float> q(n, 0.0f);
  std::vector<coding::Table> c(n);
  std::vector<int> l(n);

  for (std::size_t i = 0; i < n; i++) {
    q.at(i) = q.at(i - 1) + p.at(i).second;
    l.at(i) = -std::ceil(std::log2(p.at(i).second));
  }

  for (std::size_t i = 1; i < n; ++i) {
    c.at(i).symbol = p.at(i).first;
    c.at(i).probability = p.at(i).second;
    c.at(i).length_code = l.at(i);
    c.at(i).code = std::vector<int>(l.at(i), 0);
    for (std::size_t j = 0; j < c.at(i).code.size(); ++j) {
      q.at(i) *= 2;
      c.at(i).code.at(j) = q.at(i);
      if (q.at(i) > 1) --q.at(i);
    }
  }

  c.erase(c.begin());
  return c;
}

inline std::vector<coding::Table> coding::huffman(
    std::vector<std::pair<char, float>> p) {
  std::sort(
      p.begin(), p.end(),
      [](const std::pair<char, float> &a, const std::pair<char, float> &b) {
        return a.second > b.second;
      });
  p.insert(p.begin(), std::pair<char, float>(0, 0.0f));

  std::vector<std::pair<char, float>> q;
  std::vector<coding::Table> c;

  for (std::size_t i = 0; i < p.size(); i++) {
    q.push_back(p.at(i));
    q.push_back(std::pair<char, float>(0, p.at(i).second));
  }