#ifndef TREE_HPP
#define TREE_HPP

#include <algorithm>
#include <print>

namespace tree {
template <class T>
struct BTreeNode {
  T value;
  BTreeNode* left;
  BTreeNode* right;

  constexpr BTreeNode(const T& val) noexcept
      : value(val), left(nullptr), right(nullptr) {}
};

template <class T>
class BTree {
  BTreeNode<T>* root;

  [[nodiscard]] void removeBranch(BTreeNode<T>* p) noexcept {
    if (p != nullptr) {
      if (p->left != nullptr) removeBranch(p->left);
      if (p->right != nullptr) removeBranch(p->right);
      delete p;
    }
  }

  [[nodiscard]] void printFromUpToDown(BTreeNode<T>* p) noexcept {
    if (p != nullptr) {
      std::print("{} ", p->value);
      printFromUpToDown(p->left);
      printFromUpToDown(p->right);
    }
  }

  [[nodiscard]] void printFromLeftToRight(BTreeNode<T>* p) noexcept {
    if (p != nullptr) {
      printFromLeftToRight(p->left);
      std::print("{} ", p->value);
      printFromLeftToRight(p->right);
    }
  }

  [[nodiscard]] void printFromDownToUp(BTreeNode<T>* p) noexcept {
    if (p != nullptr) {
      printFromDownToUp(p->left);
      printFromDownToUp(p->right);
      std::print("{} ", p->value);
    }
  }

  [[nodiscard]] constexpr std::size_t getSize(BTreeNode<T>* p) const noexcept {
    if (p == nullptr) return 0;
    return 1 + getSize(p->left) + getSize(p->right);
  }

  [[nodiscard]] constexpr std::size_t getHeight(
      BTreeNode<T>* p) const noexcept {
    if (p == nullptr) return 0;
    return std::max(getHeight(p->left), getHeight(p->right)) + 1;
  }

  [[nodiscard]] constexpr std::size_t getSumLenght(
      BTreeNode<T>* p, std::size_t l) const noexcept {
    if (p == nullptr) return 0;
    return l + getSumLenght(p->left, l + 1) + getSumLenght(p->right, l + 1);
  }

 public:
  BTree() noexcept : root(nullptr) {}

  ~BTree() noexcept { clear(); }

  [[nodiscard]] constexpr void add(const T& val) noexcept {
    if (root == nullptr)
      root = new BTreeNode<T>(val);
    else {
      BTreeNode<T>* cur = root;
      BTreeNode<T>* pred = nullptr;

      do {
        pred = cur;
        if (val < cur->value)
          cur = cur->left;
        else
          cur = cur->right;
      } while (cur != nullptr);

      if (val < pred->value)
        pred->left = new BTreeNode<T>(val);
      else
        pred->right = new BTreeNode<T>(val);
    }
  }

  [[nodiscard]] void remove(const T& val) noexcept {
    if (root == nullptr) return;

    BTreeNode<T>* cur = root;
    BTreeNode<T>* prev = nullptr;

    while (cur->value != val) {
      prev = cur;

      if (val < cur->value)
        cur = cur->left;
      else
        cur = cur->right;

      if (cur == nullptr) return;
    }

    if (prev->left->value == cur->value) {
      prev->left = cur->left;
      if (cur->left == nullptr) prev->left = cur->right;
    } else {
      prev->right = cur->left;
      if (cur->left == nullptr) prev->right = cur->right;
    }
    delete cur;
  }

  [[nodiscard]] void clear() noexcept {
    removeBranch(root);
    root = nullptr;
  }

  [[nodiscard]] void printFromUpToDown() noexcept {
    printFromUpToDown(root);
    std::print("\n");
  }

  [[nodiscard]] void printFromLeftToRight() noexcept {
    printFromLeftToRight(root);
    std::print("\n");
  }

  [[nodiscard]] void printFromDownToUp() noexcept {
    printFromDownToUp(root);
    std::print("\n");
  }

  [[nodiscard]] constexpr std::size_t getSize() const noexcept {
    return getSize(root);
  }

  [[nodiscard]] constexpr std::size_t getHeight() const noexcept {
    return getHeight(root);
  }

  [[nodiscard]] constexpr double getMediumHeight() const noexcept {
    return static_cast<double>(getSumLenght(root, 1)) /
           static_cast<double>(getSize(root));
  }
};
}  // namespace tree
#endif  // !TREE_HPP