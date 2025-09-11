#include <Windows.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "../include/avl_tree.hpp"
#include "../include/b_tree.hpp"
#include "../include/coding.hpp"
#include "../include/os_tree.hpp"
#include "../include/pbs_tree.hpp"
#include "../include/rs_tree.hpp"

/**
 *      1
         \
          3
         / \
        2   5
           / \
          4   6

          3 + 3 + 2 + 2 + 1 = 11
          11/6 = 1.83

8 вариант
 */
void Lab1() {
  RSTree<int> tree;
  tree.Add(1);
  tree.Add(3);
  tree.Add(2);
  tree.Add(5);
  tree.Add(4);
  tree.Add(6);

  std::print("Pre-order: ");
  tree.PrintPreOrder();
  std::print("In-order: ");
  tree.PrintInOrder();
  std::print("Post-order: ");
  tree.PrintPostOrder();

  std::println("Tree size: {}", tree.Size());
  std::println("Tree sum: {}", tree.Sum());
  std::println("Tree height: {}", tree.Height());
  std::println("Tree average height: {:.2f}", tree.AverageHeight());
}

void Lab2() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr(100);
  for (int i = 0; i < 100; i++) {
    arr[i] = dis(gen);
  }

  PBSTree<int> tree(arr);

  std::print("In-order: ");
  tree.PrintInOrder();

  std::println("Tree size: {}", tree.Size());
  std::println("Tree sum: {}", tree.Sum());
  std::println("Tree height: {}", tree.Height());
  std::println("Tree average height: {:.2f}", tree.AverageHeight());
}

void Lab3() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr;
  for (int i = 0; i < 100; i++) {
    arr.push_back(dis(gen));
  }

  RSTree<int> rs_tree;
  for (int i = 0; i < 100; i++) {
    rs_tree.Add(arr[i]);
  }

  PBSTree<int> pbs_tree(arr);

  std::print("In-order: ");
  rs_tree.PrintInOrder();

  std::println("\n n = 100 | Size | Sum | Height | Average Height");
  std::println("-----------------------------------------------");
  std::println("    PBST |{:5} |{:4} |{:7} |{:14.2f}", pbs_tree.Size(),
               pbs_tree.Sum(), pbs_tree.Height(), pbs_tree.AverageHeight());
  std::println("     RST |{:5} |{:4} |{:7} |{:14.2f}", rs_tree.Size(),
               rs_tree.Sum(), rs_tree.Height(), rs_tree.AverageHeight());

  RSTree<int> rs_tree_recursive;
  for (int i = 0; i < 100; i++) {
    rs_tree_recursive.AddRecursive(arr[i]);
  }

  std::println(" RST(rec)|{:5} |{:4} |{:7} |{:14.2f}", rs_tree_recursive.Size(),
               rs_tree_recursive.Sum(), rs_tree_recursive.Height(),
               rs_tree_recursive.AverageHeight());
}

void Lab4() {
  RSTree<int> tree;
  std::vector<int> arr(10);

  std::println("Enter 10 integers:");
  for (int &elem : arr) {
    std::cin >> elem;
    tree.Add(elem);
  }

  tree.PrintInOrder();

  for (int elem : arr) {
    tree.Remove(elem);
    tree.PrintInOrder();
  }
}

void Lab5() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  AVLTree<int> avl_tree;
  PBSTree<int> pbs_tree;
  std::vector<int> arr;

  for (int i = 0; i < 100; i++) {
    int value = dis(gen);
    arr.push_back(value);
    avl_tree.Add(value);
  }

  pbs_tree = PBSTree<int>(arr);

  std::print("In-order: ");
  avl_tree.PrintInOrder();

  std::println("\n n = 100 | Size | Sum | Height | Average Height");
  std::println("-----------------------------------------------");
  std::println("     PBS |{:5} |{:4} |{:7} |{:14.2f}", pbs_tree.Size(),
               pbs_tree.Sum(), pbs_tree.Height(), pbs_tree.AverageHeight());
  std::println("     AVL |{:5} |{:4} |{:7} |{:14.2f}", avl_tree.Size(),
               avl_tree.Sum(), avl_tree.Height(), avl_tree.AverageHeight());
}

void Lab6() {
  AVLTree<int> tree;
  std::vector<int> arr(10);

  std::println("Enter 10 integers:");
  for (int &elem : arr) {
    std::cin >> elem;
    tree.Add(elem);
  }

  tree.PrintInOrder();

  for (int elem : arr) {
    tree.Remove(elem);
    tree.PrintInOrder();
  }
}
void Lab7() {
  BTree<int, 3> b_tree;
  AVLTree<int> avl_tree;

  for (int i = 0; i < 20; i++) {
    b_tree.Add(i);
    avl_tree.Add(i);
  }

  std::println("=== Initial State ===");
  std::print("B-tree in-order: ");
  b_tree.PrintInOrder();
  std::print("AVL tree in-order: ");
  avl_tree.PrintInOrder();

  std::println("\n n = 20 | Size | Sum | Height | Average Height");
  std::println("-----------------------------------------------");
  std::println("     AVL |{:5} |{:4} |{:7} |{:14.2f}", avl_tree.Size(),
               avl_tree.Sum(), avl_tree.Height(), avl_tree.AverageHeight());
  std::println("   B-tree|{:5} |{:4} |{:7} |{:14.2f}", b_tree.Size(),
               b_tree.Sum(), b_tree.Height(), b_tree.AverageHeight());

  std::vector<int> elements_to_remove = {5, 10, 15, 3, 8, 12, 18, 1, 7, 14};

  std::println("\n=== Step-by-step removal from B-tree ===");

  for (size_t i = 0; i < elements_to_remove.size(); i++) {
    int elem = elements_to_remove[i];

    std::println("\nStep {}: Removing element {}", i + 1, elem);

    bool element_exists = b_tree.Contains(elem);

    if (element_exists) {
      b_tree.Remove(elem);
      std::print("After removing {}: ", elem);
      b_tree.PrintInOrder();

      std::println("Size: {}, Height: {}, Avg Height: {:.2f}", b_tree.Size(),
                   b_tree.Height(), b_tree.AverageHeight());
    } else {
      std::println("Element {} not found in the tree", elem);
    }

    if (avl_tree.Contains(elem)) {
      avl_tree.Remove(elem);
    }

    if ((i + 1) % 3 == 0) {
      std::println("\n--- Comparison after {} removals ---", i + 1);
      std::print("B-tree: ");
      b_tree.PrintInOrder();
      std::print("AVL tree: ");
      avl_tree.PrintInOrder();

      std::println("B-tree  - Size: {}, Height: {}, Avg Height: {:.2f}",
                   b_tree.Size(), b_tree.Height(), b_tree.AverageHeight());
      std::println("AVL tree - Size: {}, Height: {}, Avg Height: {:.2f}",
                   avl_tree.Size(), avl_tree.Height(),
                   avl_tree.AverageHeight());
    }
  }

  std::println("\n=== Final State ===");
  std::print("B-tree final: ");
  b_tree.PrintInOrder();
  std::print("AVL tree final: ");
  avl_tree.PrintInOrder();

  std::println("\nFinal statistics:");
  std::println("B-tree  - Size: {}, Height: {}, Avg Height: {:.2f}",
               b_tree.Size(), b_tree.Height(), b_tree.AverageHeight());
  std::println("AVL tree - Size: {}, Height: {}, Avg Height: {:.2f}",
               avl_tree.Size(), avl_tree.Height(), avl_tree.AverageHeight());

  std::println("\n=== B-tree structure analysis ===");
  std::println("B-tree node capacity: {}", 3);
  std::println("Minimum keys per node: {}", (3 - 1) / 2);
  std::println("Maximum keys per node: {}", 3 - 1);

  std::println("\n=== Search examples ===");
  std::vector<int> test_elements = {2, 6, 11, 16, 19};

  for (int elem : test_elements) {
    bool exists = b_tree.Contains(elem);
    std::println("Element {}: {}", elem, exists ? "exists" : "not found");
  }
}

void Lab8() {
  SetConsoleOutputCP(CP_UTF8);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  const std::size_t size = 7;
  std::vector<std::pair<int, uint64_t>> arr;

  for (int i = 0; i < size; i++) {
    arr.push_back({i, dis(gen)});
  }

  std::print("Base array: ");
  for (const auto &elem : arr) std::print("{} ", elem.first);
  std::println();

  std::print("Weights: ");
  for (const auto &elem : arr) std::print("{} ", elem.second);
  std::println("\n");

  EOSTree<int> eost_tree(arr);
  std::print("Tree in-order: ");
  eost_tree.PrintInOrder();

  std::println("AW matrix:");
  eost_tree.PrintAW();

  std::println("AP matrix:");
  eost_tree.PrintAP();

  std::println("AR matrix:");
  eost_tree.PrintAR();

  std::println("\nAP[0,size] / AW[0,size] = {:.3f}",
               static_cast<double>(eost_tree.GetAP()[0][size]) /
                   eost_tree.GetAW()[0][size]);

  std::println("Weighted average height: {:.3f}",
               eost_tree.GetWeightedAverageHeight());

  std::println("\n n = {:3} | Size | Sum | Height | Average Height", size);
  std::println("-----------------------------------------------");
  std::println("     EOS |{:5} |{:4} |{:7} |{:14.2f}", eost_tree.Size(),
               eost_tree.Sum(), eost_tree.Height(), eost_tree.AverageHeight());
}

void Lab9() {
  SetConsoleOutputCP(CP_UTF8);

  const int size = 100;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, size);

  std::vector<std::pair<int, uint64_t>> arr;
  for (int i = 0; i < size; i++) {
    arr.push_back({i, dis(gen)});
  }

  EOSTree<int> eost_tree(arr);
  OSTreeA1<int> a1_tree(arr);
  OSTreeA2<int> a2_tree(arr);

  std::print("A1 tree in-order: ");
  a1_tree.PrintInOrder();

  std::print("A2 tree in-order: ");
  a2_tree.PrintInOrder();

  std::println("\n n = {:3} | Size | Sum | Height | Average Height", size);
  std::println("-----------------------------------------------");
  std::println("     EOS |{:5} |{:4} |{:7} |{:14.2f}", eost_tree.Size(),
               eost_tree.Sum(), eost_tree.Height(), eost_tree.AverageHeight());
  std::println("      A1 |{:5} |{:4} |{:7} |{:14.2f}", a1_tree.Size(),
               a1_tree.Sum(), a1_tree.Height(), a1_tree.AverageHeight());
  std::println("      A2 |{:5} |{:4} |{:7} |{:14.2f}", a2_tree.Size(),
               a2_tree.Sum(), a2_tree.Height(), a2_tree.AverageHeight());
}

void Lab11(std::vector<coding::Table> &alphabet,
           std::vector<coding::Table> &str) {
  coding::FanoA2(alphabet);

  std::size_t max_length = 0;
  for (const coding::Table &table : alphabet) {
    if (max_length < table.code.size()) {
      max_length = table.code.size();
    }
  }

  std::println(" Char | Probability |   Code | Length");
  std::println("-------------------------------------");

  for (const coding::Table &table : alphabet) {
    std::string code_str;
    for (int bit : table.code) {
      code_str += std::to_string(bit);
    }

    std::println(" {:>4} | {:11.6f} | {:>{}} | {:6}", table.symbol,
                 table.probability, code_str, max_length, table.code.size());
  }

  double sum = 0.0;
  for (const coding::Table &table : alphabet) {
    sum += 1.0 / std::pow(2.0, table.code.size());
  }

  double avg_length = coding::CalculateAverageCodeLength(alphabet);
  double entropy = coding::CalculateEntropy(alphabet);
  double redundancy = avg_length - entropy;

  std::println("\nKraft inequality: {:.6f} <= 1", sum);
  std::println("Entropy: {:.6f}", entropy);
  std::println("Average code length: {:.6f}", avg_length);
  std::println("Redundancy: {:.6f}", redundancy);

  std::print("\nText: ");
  for (coding::Table &s : str) {
    for (coding::Table &t : alphabet) {
      if (s.symbol == t.symbol) {
        s.code = t.code;
        break;
      }
    }
    std::print("{}", s.symbol);
  }

  std::print("\nCode: ");
  std::size_t code_size = 0;
  for (const coding::Table &s : str) {
    for (int bit : s.code) {
      std::print("{}", bit);
      code_size++;
    }
  }

  std::println("\nOriginal size: 800 bits");
  std::println("Encoded size: {} bits", code_size);
  std::println("Compression ratio: {:.3f}",
               static_cast<double>(code_size) / 800.0);
}

void Lab10_13() {
  SetConsoleOutputCP(CP_UTF8);

  const std::string file_name = "chars.txt";
  const int file_size = 10240;

  std::vector<coding::Table> alphabet;
  for (char c = 'a'; c <= 'z'; c++) {
    alphabet.push_back({static_cast<int>(c), 0.0});
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

  std::ofstream file_out(file_name);
  for (int i = 0; i < file_size; i++) {
    char c = alphabet[dis(gen)].symbol;
    file_out << c;
  }
  file_out.close();

  std::ifstream file_in(file_name);
  char c;
  int total_chars = 0;

  while (file_in.get(c)) {
    for (coding::Table &symbol : alphabet) {
      if (c == symbol.symbol) {
        symbol.probability += 1.0;
        total_chars++;
        break;
      }
    }
  }
  file_in.close();

  for (coding::Table &symbol : alphabet) {
    symbol.probability /= total_chars;
  }

  // coding::Shennon(alphabet);    // Lab 10
  // coding::Fano(alphabet);       // Lab 11
  // coding::Huffman(alphabet);  // Lab 12
  // coding::GilbertMur(alphabet); // Lab 13

  coding::PrintCodes(alphabet);

  std::vector<coding::Table> test_string;
  for (int i = 0; i < 100; i++) {
    test_string.push_back(alphabet[dis(gen)]);
  }

  Lab11(alphabet, test_string);
}

void Lab14() {
  SetConsoleOutputCP(CP_UTF8);

  std::string text =
      "December is a magical month when the boundaries between reality and "
      "fairy tales are blurred, and snow, like a fluffy feather bed, covers "
      "the earth.";
  std::string word = "snow";

  std::println("Text: {}", text);
  std::println("Word: {}", word);

  auto [naivePositions, naiveCompares] = coding::NaiveSearch(text, word);
  std::print("Simple search indexes: ");
  for (auto idx : naivePositions) std::print("{} ", idx);
  std::println("\nCompares: {}", naiveCompares);

  auto [rkPositions, rkCompares] = coding::RabinKarp(text, word);
  std::print("Rabin-Karp indexes: ");
  for (auto idx : rkPositions) std::print("{} ", idx);
  std::println("\nCompares: {}", rkCompares);
}

int main() {
  std::println("=== Data Structures and Algorithms Labs ===\n");

  // std::println("Lab 1 - Basic Binary Tree");
  // Lab1();

  std::println("\nLab 2 - Perfectly Balanced Tree");
  Lab2();

  // std::println("\nLab 3 - Random search tree build");
  // Lab3();

  // std::println("\nLab 4 - Random search Tree Remove Operations");
  // Lab4();

  // std::println("\nLab 5 - AVL Tree");
  // Lab5();

  // std::println("\nLab 6 - AVL Tree Operations");
  // Lab6();

  // std::println("\nLab 7 - B-tree");
  // Lab7();

  // std::println("\nLab 8 - Optimal Search Tree");
  //  Lab8();

  // std::println("\nLab 9 - OST Algorithms Comparison");
  // Lab9();

  // std::println("\nLabs 10-13 - Coding Algorithms");
  // Lab10_13();

  // std::println("\nLab 14 - String Search");
  // Lab14();

  return 0;
}