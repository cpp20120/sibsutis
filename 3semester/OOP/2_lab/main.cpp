#include <print>
#include <random>
#include <iostream>

int** createMatrix(const std::size_t N) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  int** mat = new int* [N];
  for (std::size_t i = 0; i < N; i++) {
    mat[i] = new int[N];
    for (std::size_t j = 0; j < N; j++)
      mat[i][j] = dis(gen);
  }
  return mat;
}

void printArr(int* arr, const std::size_t N) {
  for (std::size_t i = 0; i < N; i++)
    std::print("{:4} ", arr[i]);
  std::println("");
}

void printMat(int** mat, const std::size_t N) {
  std::println("Matrix:");

  for (std::size_t i = 0; i < N; i++)
    printArr(mat[i], N);
  std::println("");
}


void getRightDiagonal(int** mat, const std::size_t N) {
  int* D = new int[N];

  for (std::size_t i = 0; i < N; i++)
    D[i] = mat[i][N - i - 1];

  std::print("Right diagonal: ");
  printArr(D, N);

  delete[] D;
}

void getLeftDiagonal(int** mat, const std::size_t N) {
  int* D = new int[N];

  for (std::size_t i = 0; i < N; i++)
    D[i] = mat[i][i];

  std::print("Left diagonal: ");
  printArr(D, N);

  delete[] D;
}

void spiralFromCenter(int** mat, const std::size_t N) {
  int* D = new int[N * N];

  std::size_t x = N / 2, y = N / 2;
  std::size_t line = 1, max_line = 1;
  enum Dir {
    up,
    left,
    down,
    right
  };
  Dir dir = up;

  for (std::size_t i = 0; i < N * N; i++) {
    D[i] = mat[y][x];

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
  }

  std::print("Spiral from centerl: ");
  printArr(D, N * N);

  delete[] D;
}

void spiralFromTopLeft(int** mat, const std::size_t N) {
  int* D = new int[N * N];

  std::size_t x = 0, y = 0;
  std::size_t line = N - 1, max_line = N;
  enum Dir {
    up,
    left,
    down,
    right
  };
  Dir dir = down;

  for (std::size_t i = 0; i < N * N; i++) {
    D[i] = mat[y][x];

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
  printArr(D, N * N);

  delete[] D;
}

void freeMem(int** mat, const std::size_t N) {
  for (std::size_t i = 0; i < N; i++) delete[] mat[i];
  delete[] mat;
}

auto main() -> int {
  std::println("-----------------First task-----------------");

  std::print("Enter a number: ");
  std::size_t N;
  std::cin >> N;
  std::println("");
  
  int** mat = createMatrix(N);
  printMat(mat, N);
  
  getRightDiagonal(mat, N);
  getLeftDiagonal(mat, N);
  spiralFromCenter(mat, N);
  spiralFromTopLeft(mat, N);

  freeMem(mat, N);
}
