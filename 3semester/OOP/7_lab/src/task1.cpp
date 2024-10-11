#include "../include/task1.hpp"

#include <print>

list<list<int>> createMatrix(std::size_t N) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  list<list<int>> mat(N);

  for (auto& inside_list : mat)
    for (std::size_t i = 0; i < N; i++) inside_list.push_back(dis(gen));

  return mat;
}

void printMat(const list<list<int>>& mat) {
  std::println("Matrix:");

  for (const auto& inside_list : mat) printArr(inside_list);
  std::println("");
}

void printArr(const list<int>& arr) {
  for (const auto& elem : arr) std::print("{:4} ", elem);
  std::println("");
}

void getRightDiagonal(const list<list<int>>& mat) {
  list<int> D(mat.size() * mat.size());

  auto I = D.begin();
  for (std::size_t n = 0; n < mat.size(); n++) {
    for (std::size_t i = 0; i <= n; i++) {
      auto it = mat.begin();
      for (std::size_t j = 0; j < i; j++) it++;

      auto it_it = it->begin();
      for (std::size_t j = 0; j < n - i; j++) it_it++;

      *I = *it_it;
      I++;
    }
  }
  for (std::size_t n = 1; n < mat.size(); n++) {
    for (std::size_t i = 0; i < mat.size() - n; i++) {
      auto it = mat.begin();
      for (std::size_t j = 0; j < i + n; j++) it++;

      auto it_it = it->begin();
      for (std::size_t j = 0; j < mat.size() - i - 1; j++) it_it++;

      *I = *it_it;
      I++;
    }
  }

  std::print("Right diagonal: ");
  printArr(D);
}

void getLeftDiagonal(const list<list<int>>& mat) {
  list<int> D(mat.size() * mat.size());

  auto I = D.begin();
  for (std::size_t n = 0; n < mat.size(); n++) {
    for (std::size_t i = 0; i <= n; i++) {
      auto it = mat.begin();
      for (std::size_t j = 0; j < i + mat.size() - 1 - n; j++) it++;

      auto it_it = it->begin();
      for (std::size_t j = 0; j < i; j++) it_it++;

      *I = *it_it;
      I++;
    }
  }
  for (std::size_t n = 1; n < mat.size(); n++) {
    for (std::size_t i = 0; i < mat.size() - n; i++) {
      auto it = mat.begin();
      for (std::size_t j = 0; j < i; j++) it++;

      auto it_it = it->begin();
      for (std::size_t j = 0; j < i + n; j++) it_it++;

      *I = *it_it;
      I++;
    }
  }

  std::print("Left diagonal: ");
  printArr(D);
}

void spiralFromCenter(const list<list<int>>& mat) {
  list<int> D(mat.size() * mat.size());

  std::size_t x = mat.size() / 2, y = mat.size() / 2;

  std::size_t line = 1, max_line = 1;
  enum Dir { up, left, down, right };
  Dir dir = up;

  std::size_t i = 0;
  for (auto& d : D) {
    auto y_it = mat.begin();
    for (std::size_t j = 0; j < y; j++) y_it++;

    auto x_it = y_it->begin();
    for (std::size_t j = 0; j < x; j++) x_it++;

    d = *x_it;

    switch (dir) {
      case up:
        y--;
        line--;
        if (line == 0) {
          dir = left;
          line = max_line;
        }
        break;

      case left:
        x--;
        line--;
        if (line == 0) {
          dir = down;
          max_line += (i == 3) ? 2 : 1;
          line = max_line;
        }
        break;

      case down:
        y++;
        line--;
        if (line == 0) {
          dir = right;
          line = max_line;
        }
        break;

      case right:
        x++;
        line--;
        if (line == 0) {
          dir = up;
          max_line++;
          line = max_line;
        }
        break;
    }
    i++;
  }

  std::print("Spiral from centerl: ");
  printArr(D);
}

void spiralFromTopLeft(const list<list<int>>& mat) {
  list<int> D(mat.size() * mat.size());

  std::size_t x = 0, y = 0;
  std::size_t line = mat.size() - 1, max_line = mat.size();
  enum Dir { up, left, down, right };
  Dir dir = down;

  for (auto& d : D) {
    auto y_it = mat.begin();
    for (std::size_t j = 0; j < y; j++) y_it++;

    auto x_it = y_it->begin();
    for (std::size_t j = 0; j < x; j++) x_it++;

    d = *x_it;

    switch (dir) {
      case up:
        y--;
        line--;
        if (line == 0) {
          dir = left;
          max_line--;
          line = max_line;
        }
        break;

      case left:
        x--;
        line--;
        if (line == 0) {
          dir = down;
          line = max_line;
        }
        break;

      case down:
        y++;
        line--;
        if (line == 0) {
          dir = right;
          max_line--;
          line = max_line;
        }
        break;

      case right:
        x++;
        line--;
        if (line == 0) {
          dir = up;
          line = max_line;
        }
        break;
    }
  }

  std::print("Spiral from top left: ");
  printArr(D);
}

void task1() {
  std::println("-----------------First task-----------------");

  std::print("Enter a number: ");
  std::size_t N;
  std::cin >> N;
  std::println("");

  auto mat = createMatrix(N);
  printMat(mat);

  getRightDiagonal(mat);
  getLeftDiagonal(mat);
  spiralFromCenter(mat);
  spiralFromTopLeft(mat);
}
