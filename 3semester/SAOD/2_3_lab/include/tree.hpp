#pragma once

#include <algorithm>
#include <concepts>
#include <memory>
#include <print>
#include <vector>


template <typename T>
concept Arithmetic = requires(T a, T b) {
  { a < b } -> std::convertible_to<bool>;
  { a + b } -> std::same_as<T>;
};

template <Arithmetic T>
struct BTreeNode {
  T value;
  std::unique_ptr<BTreeNode> left{}, right{};

  explicit BTreeNode(const T& val)
      : value(val), left(nullptr), right(nullptr) {}
};

template <Arithmetic T>
class ITree {

 protected:
  std::unique_ptr<BTreeNode<T>> root{};

  static void constexpr removeBranch(
      std::unique_ptr<BTreeNode<T>>& p) noexcept {
    if (p) {
      removeBranch(p->left);
      removeBranch(p->right);
    }
  }

   void printFromUpToDown(const BTreeNode<T>* p) const noexcept {
    if (p) {
      std::print("{} ", p->value);
      printFromUpToDown(p->left.get());
      printFromUpToDown(p->right.get());
    }
  }

   void printFromLeftToRight(
      const BTreeNode<T>* p) const noexcept {
    if (p) {
      printFromLeftToRight(p->left.get());
      std::print("{} ", p->value);
      printFromLeftToRight(p->right.get());
    }
  }

  void printFromDownToUp(const BTreeNode<T>* p) const noexcept {
    if (p) {
      printFromDownToUp(p->left.get());
      printFromDownToUp(p->right.get());
      std::print("{} ", p->value);
    }
  }

  [[nodiscard]] static constexpr std::size_t getSize(
      const BTreeNode<T>* p) noexcept {
    return p ? 1 + getSize(p->left.get()) + getSize(p->right.get()) : 0;
  }

  [[nodiscard]] static constexpr std::size_t getHeight(
      const BTreeNode<T>* p) noexcept {
    return p ? std::max(getHeight(p->left.get()), getHeight(p->right.get())) + 1
             : 0;
  }

  [[nodiscard]] static constexpr std::size_t getSumLength(
      const BTreeNode<T>* p, std::size_t l) noexcept {
    return p ? l + getSumLength(p->left.get(), l + 1) +
                   getSumLength(p->right.get(), l + 1)
             : 0;
  }

  [[nodiscard]] static constexpr T getSum(const BTreeNode<T>* p) noexcept {
    return p ? p->value + getSum(p->left.get()) + getSum(p->right.get()) : T{};
  }

  [[nodiscard]] void add(const T& val) noexcept {
    if (!this->root) {
      this->root = std::make_unique<BTreeNode<T>>(val);
    } else {
      BTreeNode<T>* cur = this->root.get();
      BTreeNode<T>* pred = nullptr;

      while (cur) {
        pred = cur;
        if (val < cur->value) {
          cur = cur->left.get();
        } else if (val > cur->value) {
          cur = cur->right.get();
        } else {
          return;
        }
      }

      if (val < pred->value)
        pred->left = std::make_unique<BTreeNode<T>>(val);
      else
        pred->right = std::make_unique<BTreeNode<T>>(val);
    }
  }
  [[nodiscard]] static void getArrayElementsFromLeftToRight(
      const BTreeNode<T>* p, std::vector<T>& arr) noexcept {
    if (p) {
      getArrayElementsFromLeftToRight(p->left.get(), arr);
      arr.push_back(p->value);
      getArrayElementsFromLeftToRight(p->right.get(), arr);
    }
  }

  [[nodiscard]] static void getArrayElementsFromUpToDown(
      const BTreeNode<T>* p, std::vector<T>& arr) noexcept {
    if (p) {
      arr.push_back(p->value);
      getArrayElementsFromUpToDown(p->left.get(), arr);
      getArrayElementsFromUpToDown(p->right.get(), arr);
    }
  }
  [[nodiscard]] static BTreeNode<T>* removeNode(
      std::unique_ptr<BTreeNode<T>>& node, const T& val) {
    if (!node) return nullptr;

    if (val < node->value) {
      node->left = removeNode(node->left, val);
    } else if (val > node->value) {
      node->right = removeNode(node->right, val);
    } else {
      if (!node->left) {
        return std::move(node->right);
      } else if (!node->right) {
        return std::move(node->left);
      }

      auto& successor = node->right;
      while (successor->left) {
        successor = successor->left;
      }

      node->value = successor->value;
      node->right = removeNode(node->right, successor->value);
    }
    return std::move(node);
  }

 public:
  constexpr ITree() noexcept : root{} {}

  [[nodiscard]] constexpr ITree(const ITree<T>& other) : root{} {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(other.root.get(), arr);
    for (const T& elem : arr) add(elem);
  }

  ~ITree() noexcept { clear(); }

  [[nodiscard]] constexpr void clear() noexcept { removeBranch(root); }

  [[nodiscard]] constexpr void printFromUpToDown() const noexcept {
    printFromUpToDown(root.get());
  }

  [[nodiscard]] constexpr void printFromLeftToRight() const noexcept {
    printFromLeftToRight(root.get());
  }

  [[nodiscard]] constexpr void printFromDownToUp() const noexcept {
    printFromDownToUp(root.get());
  }

  [[nodiscard]] constexpr std::size_t getSize() const noexcept {
    return getSize(root.get());
  }

  [[nodiscard]] constexpr std::size_t getHeight() const noexcept {
    return getHeight(root.get());
  }

  [[nodiscard]] constexpr double getMediumHeight() const noexcept {
    return static_cast<double>(getSumLength(root.get(), 1)) /
           static_cast<double>(getSize(root.get()));
  }

  [[nodiscard]] constexpr T getSum() const noexcept {
    return getSum(root.get());
  }

  [[nodiscard]] constexpr void remove(const T& val) noexcept {
    removeNode(root, val);
  }
  [[nodiscard]] constexpr T get(std::size_t index) const noexcept {
    std::vector<T> arr(getSize());
    getArrayElementsFromLeftToRight(root.get(), arr);
    return arr[index];
  }

  [[nodiscard]] constexpr std::vector<T> getArrayElementsFromLeftToRight()
      const noexcept {
    std::vector<T> arr;
    getArrayElementsFromLeftToRight(root.get(), arr);
    return arr;
  }

  [[nodiscard]] constexpr std::vector<T> getArrayElementsFromUpToDown()
      const noexcept {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(root.get(), arr);
    return arr;
  }
};

template <Arithmetic T>
class BTree : public ITree<T> {
 public:
  [[nodiscard]] void add(const T& val) noexcept {
    if (!this->root) {
      this->root = std::make_unique<BTreeNode<T>>(val);
      return;
    }

    BTreeNode<T>* cur = this->root.get();
    BTreeNode<T>* parent = nullptr;

    while (cur) {
      parent = cur;
      if (val < cur->value) {
        cur = cur->left.get();
      } else if (val > cur->value) {
        cur = cur->right.get();
      } else {
        return;
      }
    }

    if (val < parent->value) {
      parent->left = std::make_unique<BTreeNode<T>>(val);
    } else {
      parent->right = std::make_unique<BTreeNode<T>>(val);
    }
  }
};

template <Arithmetic T>
class PBSTree : public ITree<T> {
 private:
  [[nodiscard]] constexpr std::unique_ptr<BTreeNode<T>> newTree(
      int64_t left, int64_t right, const std::vector<T>& arr) noexcept {
    if (left > right) return nullptr;
    std::size_t medium = (left + right) / 2;
    auto p = std::make_unique<BTreeNode<T>>(arr[medium]);
    p->left = newTree(left, medium - 1, arr);
    p->right = newTree(medium + 1, right, arr);
    return p;
  }

 public:
  PBSTree() noexcept : ITree<T>{} {}
  [[nodiscard]] PBSTree(const std::vector<T>& arr) noexcept {
    this->root = newTree(0, arr.size() - 1, arr);
  }

  [[nodiscard]] constexpr void add(const T& val) noexcept {
    std::vector<T> arr = this->getArrayElementsFromLeftToRight();
    arr.push_back(val);
    std::sort(arr.begin(), arr.end());
    this->clear();
    this->root = newTree(0, arr.size() - 1, arr);
  }
};
