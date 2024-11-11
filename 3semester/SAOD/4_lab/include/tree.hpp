#pragma once

#include <algorithm>
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
  std::unique_ptr<BTreeNode> left, right;

  [[nodiscard]] constexpr BTreeNode(const T& val)
      : value(val), left(nullptr), right(nullptr) {}
};

template <Arithmetic T>
class ITree {
 protected:
  std::unique_ptr<BTreeNode<T>> root;

  [[nodiscard]] static constexpr void removeBranch(
      std::unique_ptr<BTreeNode<T>>& p) noexcept {
    p.reset();
  }

  [[nodiscard]] static constexpr void printFromUpToDown(
      const BTreeNode<T>* p) noexcept {
    if (p != nullptr) {
      std::print("{} ", p->value);
      printFromUpToDown(p->left.get());
      printFromUpToDown(p->right.get());
    }
  }

  [[nodiscard]] static constexpr void printFromLeftToRight(
      const BTreeNode<T>* p) noexcept {
    if (p != nullptr) {
      printFromLeftToRight(p->left.get());
      std::print("{} ", p->value);
      printFromLeftToRight(p->right.get());
    }
  }

  [[nodiscard]] static constexpr void printFromDownToUp(
      const BTreeNode<T>* p) noexcept {
    if (p != nullptr) {
      printFromDownToUp(p->left.get());
      printFromDownToUp(p->right.get());
      std::print("{} ", p->value);
    }
  }

  [[nodiscard]] static constexpr std::size_t getSize(
      const BTreeNode<T>* p) noexcept {
    if (p == nullptr) return 0;
    return 1 + getSize(p->left.get()) + getSize(p->right.get());
  }

  [[nodiscard]] static constexpr std::size_t getHeight(
      const BTreeNode<T>* p) noexcept {
    if (p == nullptr) return 0;
    return std::max(getHeight(p->left.get()), getHeight(p->right.get())) + 1;
  }

  [[nodiscard]] static constexpr std::size_t getSumLength(
      const BTreeNode<T>* p, std::size_t l) noexcept {
    if (p == nullptr) return 0;
    return l + getSumLength(p->left.get(), l + 1) +
           getSumLength(p->right.get(), l + 1);
  }

  [[nodiscard]] static constexpr T getSum(const BTreeNode<T>* p) {
    if (p == nullptr) return 0;
    return p->value + getSum(p->left.get()) + getSum(p->right.get());
  }

  [[nodiscard]] static constexpr void getArrayElementsFromLeftToRight(
      const BTreeNode<T>* p, std::vector<T>& arr) noexcept {
    if (p != nullptr) {
      getArrayElementsFromLeftToRight(p->left.get(), arr);
      arr.push_back(p->value);
      getArrayElementsFromLeftToRight(p->right.get(), arr);
    }
  }

  [[nodiscard]] static constexpr void getArrayElementsFromUpToDown(
      const BTreeNode<T>* p, std::vector<T>& arr) noexcept {
    if (p != nullptr) {
      arr.push_back(p->value);
      getArrayElementsFromUpToDown(p->left.get(), arr);
      getArrayElementsFromUpToDown(p->right.get(), arr);
    }
  }

  [[nodiscard]] constexpr void remove(std::unique_ptr<BTreeNode<T>>& cur,
                                      BTreeNode<T>* prev,
                                      const T& value) noexcept {
    if (cur == nullptr) return;
    if (getSize() == 1) {
      cur.reset();
      root.reset();
      return;
    }

    if (cur->value != value) {
      if (cur->value > value)
        remove(cur->left, cur.get(), value);
      else
        remove(cur->right, cur.get(), value);
    } else {
      if (cur->right != nullptr) {
        auto cur_left = std::move(cur->left);
        cur = std::move(cur->right);

        if (prev != nullptr) {
          if (cur->value < prev->value)
            prev->left = std::move(cur);
          else
            prev->right = std::move(cur);
        } else
          root = std::move(cur);

        while (cur->left != nullptr) cur = std::move(cur->left);
        cur->left = std::move(cur_left);
      } else if (cur->left != nullptr) {
        auto cur_right = std::move(cur->right);
        cur = std::move(cur->left);

        if (prev != nullptr) {
          if (cur->value < prev->value)
            prev->left = std::move(cur);
          else
            prev->right = std::move(cur);
        } else
          root = std::move(cur);

        while (cur->right != nullptr)
          cur = std::move(cur->right);  // Move right
        cur->right = std::move(cur_right);
      } else {
        if (cur->value < prev->value)
          prev->left.reset();
        else
          prev->right.reset();
      }
    }
  }

 public:
  ITree() : root(nullptr) {}

  ITree(const ITree<T>& other) : ITree() {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(other.root.get(), arr);
    for (T& elem : arr) add(elem);
  }

  ~ITree() { clear(); }

  [[nodiscard]] constexpr void clear() noexcept { removeBranch(root); }

  [[nodiscard]] constexpr void printFromUpToDown() noexcept {
    printFromUpToDown(root.get());
    std::print("\n");
  }

  [[nodiscard]] constexpr void printFromLeftToRight() noexcept {
    printFromLeftToRight(root.get());
    std::print("\n");
  }

  [[nodiscard]] constexpr void printFromDownToUp() noexcept {
    printFromDownToUp(root.get());
    std::print("\n");
  }

  [[nodiscard]] constexpr std::size_t getSize() noexcept {
    return getSize(root.get());
  }

  [[nodiscard]] constexpr std::size_t getHeight() noexcept {
    return getHeight(root.get());
  }

  [[nodiscard]] constexpr double getMediumHeight() noexcept {
    return static_cast<double>(getSumLength(root.get(), 1)) /
           static_cast<double>(getSize(root.get()));
  }

  [[nodiscard]] constexpr T getSum() { return getSum(root.get()); }

  [[nodiscard]] constexpr void remove(const T& val) noexcept {
    remove(root, nullptr, val);
  }

  [[nodiscard]] constexpr T get(std::size_t index) noexcept {
    std::vector<T> arr(getSize());
    getArrayElementsFromLeftToRight(root.get(), arr);
    return arr[index];
  }

  [[nodiscard]] constexpr std::vector<T>
  getArrayElementsFromLeftToRight() noexcept {
    std::vector<T> arr;
    getArrayElementsFromLeftToRight(root.get(), arr);
    return arr;
  }

  [[nodiscard]] constexpr std::vector<T>
  getArrayElementsFromUpToDown() noexcept {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(root.get(), arr);
    return arr;
  }

  virtual void add(const T&) = 0;
};

template <Arithmetic T>
class BTree : public ITree<T> {
  [[nodiscard]] constexpr std::unique_ptr<BTreeNode<T>> __addRecurs(
      const T& val, std::unique_ptr<BTreeNode<T>>& cur) noexcept {
    if (cur == nullptr) return std::make_unique<BTreeNode<T>>(val);

    if (val < cur->value)
      cur->left = __addRecurs(val, cur->left);
    else
      cur->right = __addRecurs(val, cur->right);
    return std::move(cur);
  }

 public:
  [[nodiscard]] constexpr void add(const T& val) {
    if (this->root == nullptr)
      this->root = std::make_unique<BTreeNode<T>>(val);
    else {
      BTreeNode<T>* cur = this->root.get();
      BTreeNode<T>* pred = nullptr;

      do {
        pred = cur;
        if (val < cur->value)
          cur = cur->left.get();
        else
          cur = cur->right.get();
      } while (cur != nullptr);

      if (val < pred->value)
        pred->left = std::make_unique<BTreeNode<T>>(val);
      else
        pred->right = std::make_unique<BTreeNode<T>>(val);
    }
  }

  [[nodiscard]] constexpr void addRecurs(const T& val) noexcept {
    this->root = __addRecurs(val, this->root);
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
  [[nodiscard]] constexpr PBSTree() = default;

  [[nodiscard]] constexpr PBSTree(std::vector<T> arr) noexcept {
    std::sort(arr.begin(), arr.end());
    this->root = newTree(0, arr.size() - 1, arr);
  }

  [[nodiscard]] constexpr void add(const T& val) noexcept {
    std::vector<T> arr;
    this->getArrayElementsFromLeftToRight(this->root.get(), arr);
    arr.push_back(val);
    std::sort(arr.begin(), arr.end());
    this->clear();
    this->root = newTree(0, arr.size() - 1, arr);
  }
};