#include <format>
#include <print>
#include <random>
#include <vector>

std::vector<int> genRandArray(int size, int maxValue) {
  std::vector<int> arr(size + 1);
  arr[0] = size;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, maxValue);

  for (int i = 1; i <= size; ++i) {
    arr[i] = dis(gen);
  }

  return arr;
}

auto print(const std::vector<int>& arr) {
  int size = arr[0];
  std::string output = std::format("{}: ", size);
  for (int i = 1; i <= size; ++i) {
    output += std::format("{} ", arr[i]);
  }
  std::print("{}\n", output);
}

auto main() -> int {
  std::random_device rd;
  int size = rd() % 10;
  int maxValue = 100;

  std::vector<int> arr = genRandArray(size, maxValue);
  print(arr);
  return 0;
}
