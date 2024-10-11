#include <print>

#include "./tree.hpp"

auto main() -> int {
  tree::BTree<int> tree;

  tree.add(10);
  tree.add(5);
  tree.add(20);
  tree.add(3);
  tree.add(7);
  tree.add(15);
  tree.add(30);

  std::print("Print tree from top to bottom (pre-order): ");
  tree.printFromUpToDown();

  std::print("Print tree from left to right (in-order): ");
  tree.printFromLeftToRight();

  std::print("Print tree from bottom to top (post-order): ");
  tree.printFromDownToUp();

  std::print("Tree size: {}\n", tree.getSize());
  std::print("Tree height: {}\n", tree.getHeight());
  std::print("Tree average depth: {:.2f}\n", tree.getMediumHeight());

  std::print("Removing 20 from the tree.\n");
  tree.remove(20);

  std::print("Print tree from left to right after removal (in-order): ");
  tree.printFromLeftToRight();

  std::print("Clearing the tree.\n");
  tree.clear();

  std::print("Tree size after clearing: {}\n", tree.getSize());

  return 0;
}
