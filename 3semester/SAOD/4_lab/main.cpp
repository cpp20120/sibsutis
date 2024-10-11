#include <iostream>
#include <print>
#include <random>

#include "tree.hpp"

void lab1() {
  BTree<int> tree;
  tree.add(1);
  tree.add(3);
  tree.add(2);
  tree.add(5);
  tree.add(4);
  tree.add(6);

  std::print("From up to down: ");
  tree.printFromUpToDown();
  std::print("From left to right: ");
  tree.printFromLeftToRight();
  std::print("From down to up: ");
  tree.printFromDownToUp();

  std::println("Tree size: {}", tree.getSize());
  std::println("Tree sum: {}", tree.getSum());
  std::println("Tree height: {}", tree.getHeight());
  std::println("Tree medium height: {:.2f}", tree.getMediumHeight());
}

void lab2() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr(100);
  for (int i = 0; i < 100; i++) arr[i] = dis(gen);
  PBSTree<int> tree;

  std::print("From left to right: ");
  tree.printFromLeftToRight();

  std::println("Tree size: {}", tree.getSize());
  std::println("Tree sum: {}", tree.getSum());
  std::println("Tree height: {}", tree.getHeight());
  std::println("Tree medium height: {:.2f}", tree.getMediumHeight());
}

void lab3() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr;
  for (int i = 0; i < 100; i++) arr.push_back(dis(gen));

  BTree<int> RSTree;
  for (int i = 0; i < 100; i++) RSTree.add(arr[i]);

  PBSTree<int> PBSTree;

  std::print("From left to right: ");
  RSTree.printFromLeftToRight();

  std::println("\n n = 100 | Size | Sum | Height | Medium Height");

  std::println("    PBST |{:5} |{:4} |{:7} |{:14}", PBSTree.getSize(),
               PBSTree.getSum(), PBSTree.getHeight(),
               PBSTree.getMediumHeight());
  std::println("     RST |{:5} |{:4} |{:7} |{:14}", RSTree.getSize(),
               RSTree.getSum(), RSTree.getHeight(), RSTree.getMediumHeight());

  RSTree.clear();
  for (int i = 0; i < 100; i++) RSTree.add(arr[i]);

  std::println("     RST |{:5} |{:4} |{:7} |{:14}", RSTree.getSize(),
               RSTree.getSum(), RSTree.getHeight(), RSTree.getMediumHeight());
}

void lab4() {
  BTree<int> RSTree;
  std::vector<int> arr(10);

  std::print("{}", "Insert tree elements:\n");

  for (int &elem : arr) {
    std::cin >> elem;
    RSTree.add(elem);
  }

  RSTree.printFromLeftToRight();
  for (int elem : arr) {
    RSTree.remove(elem);
    RSTree.printFromLeftToRight();
  }
}

auto main() -> int {
  // std::print("{}\n", "First lab:");
  // lab1();
  // std::print("{}\n", "Second lab:");
  // lab2();
  // std::print("{}\n", "Third lab:");
  // lab3();
  std::print("{}\n", "Fourth lab:");
  lab4();
  return 0;
}
