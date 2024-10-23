#include <iostream>
#include <random>

#include "tree.hpp"

void lab1() {
  RSTree<int> tree;
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
  PBSTree<int> tree(arr);

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

  RSTree<int> rs_tree;
  for (int i = 0; i < 100; i++) rs_tree.add(arr[i]);

  PBSTree<int> pbs_tree(arr);

  std::print("From left to right: ");
  rs_tree.printFromLeftToRight();

  std::println("\n n = 100 | Size | Sum | Height | Medium Height");

  std::println("    PBST |{:5} |{:4} |{:7} |{:14}", pbs_tree.getSize(),
               pbs_tree.getSum(), pbs_tree.getHeight(),
               pbs_tree.getMediumHeight());
  std::println("     RST |{:5} |{:4} |{:7} |{:14}", rs_tree.getSize(),
               rs_tree.getSum(), rs_tree.getHeight(),
               rs_tree.getMediumHeight());

  rs_tree.clear();
  for (int i = 0; i < 100; i++) rs_tree.addRecurs(arr[i]);

  std::println("     RST |{:5} |{:4} |{:7} |{:14}", rs_tree.getSize(),
               rs_tree.getSum(), rs_tree.getHeight(),
               rs_tree.getMediumHeight());
}

void lab4() {
  RSTree<int> tree;
  std::vector<int> arr(10);

  for (int& elem : arr) {
    std::cin >> elem;
    tree.add(elem);
  }

  tree.printFromLeftToRight();

  for (int elem : arr) {
    tree.remove(elem);
    tree.printFromLeftToRight();
  }
}

void lab5() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  AVLTree<int> avl_tree;
  PBSTree<int> pbs_tree;
  std::vector<int> arr;

  for (int i = 0; i < 100; i++) arr.push_back(dis(gen));

  for (int& elem : arr) {
    avl_tree.add(elem);
    pbs_tree.add(elem);
  }

  std::print("From left to right: ");
  avl_tree.printFromLeftToRight();

  std::println("\n n = 100 | Size | Sum | Height | Medium Height");

  std::println("     PBS |{:5} |{:4} |{:7} |{:14}", pbs_tree.getSize(),
               pbs_tree.getSum(), pbs_tree.getHeight(),
               pbs_tree.getMediumHeight());
  std::println("     AVL |{:5} |{:4} |{:7} |{:14}", avl_tree.getSize(),
               avl_tree.getSum(), avl_tree.getHeight(),
               avl_tree.getMediumHeight());
}

void lab6() {
  std::print("{}\n", "Enter elements(10) of AVL tree:");
  AVLTree<int> tree;
  std::vector<int> arr(10);

  for (int& elem : arr) {
    std::cin >> elem;
    tree.add(elem);
  }

  tree.printFromLeftToRight();

  for (int elem : arr) {
    tree.remove(elem);
    tree.printFromLeftToRight();
  }
}

int main() {
  // lab1();
  // lab2();
  // lab3();
  // lab4();
  // lab5();
  lab6();

  return 0;
}