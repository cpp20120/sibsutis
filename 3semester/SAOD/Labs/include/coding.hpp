#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <list>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <vector>

namespace coding {

struct Table {
  int symbol = 0;
  double probability = 0;
  double q = 0;
  std::list<int> code;

  bool operator<(const Table& other) const {
    return probability > other.probability;
  }
};

std::pair<std::vector<size_t>, size_t> NaiveSearch(const std::string& text,
                                                   const std::string& pattern);

void Shennon(std::vector<Table>& arr);
void Fano(std::vector<Table>& arr);
void FanoA2(std::vector<Table>& arr);
void Huffman(std::vector<Table>& arr);
void GilbertMur(std::vector<Table>& arr);
std::pair<std::vector<size_t>, size_t> RabinKarp(const std::string& text,
                                                 const std::string& pattern);

double CalculateAverageCodeLength(const std::vector<Table>& arr);
double CalculateEntropy(const std::vector<Table>& arr);
double CalculateEfficiency(const std::vector<Table>& arr);
void PrintCodes(const std::vector<Table>& arr);

}  // namespace coding