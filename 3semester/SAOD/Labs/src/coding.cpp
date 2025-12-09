#include "../include/coding.hpp"

#include <print>
#include <ranges>
#include <stack>
#include <stdexcept>

namespace coding {

namespace {

constexpr double kLog2 = 0.6931471805599453;  // log(2)

inline double FastLog2(double x) { return std::log(x) / kLog2; }

inline void ClearAndSortDescending(std::vector<Table>& arr) {
  for (auto& item : arr) {
    item.code.clear();
  }
  std::ranges::sort(arr, std::greater{}, &Table::probability);
}
int FindMedian(std::vector<Table>& arr, int left, int right, bool use_a2) {
  if (left == right) return left;

  double total_weight = 0.0;
  for (int i = left; i <= right; ++i) {
    total_weight += arr[i].probability;
  }

  if (use_a2) {
    // Алгоритм A2 - ищем точку, где сумма становится >= половины
    double half_weight = total_weight / 2.0;
    double cumulative = 0.0;

    for (int i = left; i <= right; ++i) {
      cumulative += arr[i].probability;
      if (cumulative >= half_weight) {
        return i;
      }
    }
    return right;  // fallback
  } else {
    // ищем минимальную разницу сумм
    double left_sum = 0.0;
    double min_diff = std::numeric_limits<double>::max();
    int best_median = left;

    for (int i = left; i < right; ++i) {
      left_sum += arr[i].probability;
      double right_sum = total_weight - left_sum;
      double diff = std::abs(left_sum - right_sum);

      if (diff < min_diff) {
        min_diff = diff;
        best_median = i;
      }
    }
    return best_median;
  }
}

void FanoRecursive(std::vector<Table>& arr, int left, int right, bool use_a2) {
  if (left >= right) return;

  int median = FindMedian(arr, left, right, use_a2);

  // Добавляем биты к кодам
  for (int i = left; i <= median; ++i) {
    arr[i].code.push_back(0);
  }
  for (int i = median + 1; i <= right; ++i) {
    arr[i].code.push_back(1);
  }

  FanoRecursive(arr, left, median, use_a2);
  FanoRecursive(arr, median + 1, right, use_a2);
}

void FanoIterative(std::vector<Table>& arr, bool use_a2) {
  if (arr.empty()) return;

  struct Task {
    int left;
    int right;
  };

  std::stack<Task> tasks;
  tasks.push({0, static_cast<int>(arr.size()) - 1});

  while (!tasks.empty()) {
    Task current = tasks.top();
    tasks.pop();

    int left = current.left;
    int right = current.right;

    if (left >= right) continue;

    int median = FindMedian(arr, left, right, use_a2);

    for (int i = left; i <= median; ++i) {
      arr[i].code.push_back(0);
    }
    for (int i = median + 1; i <= right; ++i) {
      arr[i].code.push_back(1);
    }

    if (left < median) {
      tasks.push({left, median});
    }
    if (median + 1 < right) {
      tasks.push({median + 1, right});
    }
  }
}

}  // namespace

std::pair<std::vector<size_t>, size_t> NaiveSearch(const std::string& text,
                                                   const std::string& pattern) {
  std::vector<size_t> positions;
  size_t compares = 0;
  if (pattern.empty() || text.size() < pattern.size())
    return {positions, compares};

  for (size_t i = 0; i <= text.size() - pattern.size(); ++i) {
    size_t j = 0;
    for (; j < pattern.size(); ++j) {
      ++compares;
      if (text[i + j] != pattern[j]) break;
    }
    if (j == pattern.size()) positions.push_back(i);
  }
  return {positions, compares};
}

std::pair<std::vector<size_t>, size_t> RabinKarp(const std::string& text,
                                                 const std::string& pattern) {
  const int base = 256;
  const int mod = 101;
  std::vector<size_t> positions;
  size_t compares = 0;
  size_t n = text.size();
  size_t m = pattern.size();
  if (m == 0 || n < m) return {positions, compares};

  // вычисляем h = (base^(m-1)) % mod
  int h = 1;
  for (size_t i = 0; i < m - 1; ++i) h = (h * base) % mod;

  // начальные хэши
  int p = 0, t = 0;
  for (size_t i = 0; i < m; ++i) {
    p = (base * p + pattern[i]) % mod;
    t = (base * t + text[i]) % mod;
  }

  for (size_t i = 0; i <= n - m; ++i) {
    if (p == t) {
      size_t j = 0;
      for (; j < m; ++j) {
        ++compares;
        if (text[i + j] != pattern[j]) break;
      }
      if (j == m) positions.push_back(i);
    } else {
      ++compares;
    }

    // Сдвигаем окно
    if (i < n - m) {
      t = (base * (t - text[i] * h) + text[i + m]) % mod;
      if (t < 0) t += mod;
    }
  }

  return {positions, compares};
}

void Shennon(std::vector<Table>& arr) {
  if (arr.empty()) return;

  ClearAndSortDescending(arr);

  double cumulative_q = 0.0;
  for (auto& symbol : arr) {
    symbol.q = cumulative_q;
    cumulative_q += symbol.probability;
  }

  for (auto& symbol : arr) {
    double temp_q = symbol.q;
    int code_length =
        static_cast<int>(std::ceil(-FastLog2(symbol.probability)));

    for (int i = 0; i < code_length; ++i) {
      temp_q *= 2.0;
      symbol.code.push_back(static_cast<int>(temp_q));
      if (temp_q >= 1.0) {
        temp_q -= 1.0;
      }
    }
  }
}

void Fano(std::vector<Table>& arr) {
  if (arr.empty()) return;
  ClearAndSortDescending(arr);
  FanoIterative(arr, false);
}

void FanoA2(std::vector<Table>& arr) {
  if (arr.empty()) return;
  ClearAndSortDescending(arr);
  FanoIterative(arr, true);
}

namespace {

struct HuffmanNode {
  double probability;
  int index;
  std::list<int> code;

  HuffmanNode(double prob, int idx) : probability(prob), index(idx) {}

  bool operator>(const HuffmanNode& other) const {
    return probability > other.probability;
  }
};

}  // namespace

void Huffman(std::vector<Table>& arr) {
  if (arr.empty()) return;

  for (auto& item : arr) {
    item.code.clear();
  }

  if (arr.size() == 1) {
    arr[0].code.push_back(0);
    return;
  }

  using HuffmanQueue =
      std::priority_queue<HuffmanNode, std::vector<HuffmanNode>,
                          std::greater<HuffmanNode>>;

  HuffmanQueue queue;

  for (int i = 0; i < arr.size(); ++i) {
    queue.emplace(arr[i].probability, i);
  }

  while (queue.size() > 1) {
    HuffmanNode min1 = queue.top();
    queue.pop();
    HuffmanNode min2 = queue.top();
    queue.pop();

    HuffmanNode new_node(min1.probability + min2.probability, -1);

    if (min1.index >= 0) {
      arr[min1.index].code.push_front(0);
    } else {
      for (auto& bit : min1.code) {
        arr[bit].code.push_front(0);
      }
    }

    if (min2.index >= 0) {
      arr[min2.index].code.push_front(1);
    } else {
      for (auto& bit : min2.code) {
        arr[bit].code.push_front(1);
      }
    }

    if (min1.index >= 0) {
      new_node.code.push_back(min1.index);
    } else {
      new_node.code.insert(new_node.code.end(), min1.code.begin(),
                           min1.code.end());
    }

    if (min2.index >= 0) {
      new_node.code.push_back(min2.index);
    } else {
      new_node.code.insert(new_node.code.end(), min2.code.begin(),
                           min2.code.end());
    }

    queue.push(new_node);
  }
}

void GilbertMur(std::vector<Table>& arr) {
  if (arr.empty()) return;

  std::ranges::sort(arr, std::less{}, &Table::symbol);

  // Вычисление q значений
  double cumulative = 0.0;
  for (auto& symbol : arr) {
    symbol.q = cumulative + symbol.probability / 2.0;
    cumulative += symbol.probability;
  }

  // Генерация кодов
  for (auto& symbol : arr) {
    double temp_q = symbol.q;
    int code_length =
        static_cast<int>(std::ceil(-FastLog2(symbol.probability))) + 1;

    for (int i = 0; i < code_length; ++i) {
      temp_q *= 2.0;
      int bit = static_cast<int>(temp_q);
      symbol.code.push_back(bit);
      if (temp_q >= 1.0) {
        temp_q -= 1.0;
      }
    }
  }
}

double CalculateAverageCodeLength(const std::vector<Table>& arr) {
  double average_length = 0.0;
  for (const auto& symbol : arr) {
    average_length += symbol.probability * symbol.code.size();
  }
  return average_length;
}

double CalculateEntropy(const std::vector<Table>& arr) {
  double entropy = 0.0;
  for (const auto& symbol : arr) {
    if (symbol.probability > 0.0) {
      entropy -= symbol.probability * FastLog2(symbol.probability);
    }
  }
  return entropy;
}

double CalculateEfficiency(const std::vector<Table>& arr) {
  double entropy = CalculateEntropy(arr);
  double average_length = CalculateAverageCodeLength(arr);
  return (average_length > 0.0) ? entropy / average_length : 0.0;
}

void PrintCodes(const std::vector<Table>& arr) {
  std::println("{:>4} {:>12} {:>12} {:>15} {:>8}", "Sym", "Probability", "Q",
               "Code", "Length");

  for (const auto& symbol : arr) {
    std::string code_str;
    for (int bit : symbol.code) {
      code_str += std::to_string(bit);
    }

    std::println("{:4d} {:12.6f} {:12.6f} {:>15} {:8}", symbol.symbol,
                 symbol.probability, symbol.q, code_str, symbol.code.size());
  }

  std::println("\nAverage code length: {:.6f}",
               CalculateAverageCodeLength(arr));
  std::println("Entropy: {:.6f}", CalculateEntropy(arr));
  std::println("Efficiency: {:.6f}", CalculateEfficiency(arr));
}

}  // namespace coding