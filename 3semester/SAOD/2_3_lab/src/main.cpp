#include <random>

#include "../include/tree.hpp"

static void lab1() {
  BTree<int> btree;
  btree.add(5);
  btree.add(3);
  btree.add(8);
  btree.add(1);
  btree.add(4);
  btree.add(7);

  std::print("BTree elements (left to right): ");
  for (const auto& val : btree.getArrayElementsFromLeftToRight()) {
    std::print("{} ", val);
  }
  std::print("\n");

  std::print("BTree In-Order: ");
  btree.printFromLeftToRight();
  std::print("\n");

  std::print("BTree Pre-Order: ");
  btree.printFromUpToDown();
  std::print("\n");

  std::print("BTree Post-Order: ");
  btree.printFromDownToUp();
  std::print("\n");

  BTree<std::string> btree_string;
  btree_string.add("apple");
  btree_string.add("banana");
  btree_string.add("cherry");

  std::print("BTree (string) elements (left to right): ");
  for (const auto& val : btree_string.getArrayElementsFromLeftToRight()) {
    std::print("{} ", val);
  }
  std::print("\n");

  PBSTree<int> pbstree({5, 3, 8, 1, 4, 7});
  std::print("PBSTree elements (left to right): ");
  for (const auto& val : pbstree.getArrayElementsFromLeftToRight()) {
    std::print("{} ", val);
  }
  std::print("\n");

  std::print("PBSTree In-Order: ");
  pbstree.printFromLeftToRight();
  std::print("\n");

  std::print("PBSTree Pre-Order: ");
  pbstree.printFromUpToDown();
  std::print("\n");

  std::print("PBSTree Post-Order: ");
  pbstree.printFromDownToUp();
  std::print("\n");

  pbstree.add(6);
  std::print("PBSTree elements (left to right) after adding 6: ");
  for (const auto& val : pbstree.getArrayElementsFromLeftToRight()) {
    std::print("{} ", val);
  }
  std::print("\n");
}

static void lab2() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr(100);
  for (int i = 0; i < 100; i++) arr[i] = dis(gen);
  PBSTree<int> tree(arr);

  std::print("From left to right: ");
  tree.printFromLeftToRight();

  std::println("Tree size: {}", tree.getSize());
  std::println("Tree sum: {}", tree.getSum());
  std::println("Tree height: {}", tree.getHeight());
  std::println("Tree medium height: {:.2f}", tree.getMediumHeight());
}

static void lab3() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr;
  for (int i = 0; i < 100; i++) arr.push_back(dis(gen));

  BTree<int> RSTree;
  for (int i = 0; i < 100; i++) RSTree.add(arr[i]);

  PBSTree<int> PBSTree(arr);

  std::print("From left to right: ");
  RSTree.printFromLeftToRight();

  std::println("\n n = 100 | Size | Sum | Height | Medium Height");

  std::println("    PBST |{:5} |{:4} |{:7} |{:14}", PBSTree.getSize(),
               PBSTree.getSum(), PBSTree.getHeight(),
               PBSTree.getMediumHeight());
  std::println("     RST |{:5} |{:4} |{:7} |{:14}", RSTree.getSize(),
               RSTree.getSum(), RSTree.getHeight(), RSTree.getMediumHeight());
}

int main() {
  std::print("lab 1:\n");
  lab1();
  std::print("lab2:\n");
  lab2();
  std::print("lab3:\n");
  lab3();

  return 0;
}
