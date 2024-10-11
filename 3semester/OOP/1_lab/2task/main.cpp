#include <print>
#include <vector>
#include <random>

std::vector<int> genRandArray(int size, int maxValue) {
    std::vector<int> arr(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxValue);

    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }

    return arr;
}

void printArray(const std::vector<int>& arr) {
    std::print("{}: ", arr.size());
    for (int num : arr) {
        std::print("{} ", num);
    }
    std::print("\n");
}

void print2DArray(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        printArray(row);
    }
}

auto main() ->int {
    std::random_device rd;
    int rows = rd() % 5 + 1;
    int maxValue = 100;

    std::vector<std::vector<int>> matrix;

    for (int i = 0; i < rows; ++i) {
        int cols = rd() % 10 + 1; 
        matrix.push_back(genRandArray(cols, maxValue));
    }

    std::print("Количество строк: {}\n", rows);
    print2DArray(matrix);

    return 0;
}
