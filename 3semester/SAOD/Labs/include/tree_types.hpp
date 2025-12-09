#pragma once

#include <memory>

#undef max

template <class T>
struct TreeNode {
  T value;
  std::unique_ptr<TreeNode> left;
  std::unique_ptr<TreeNode> right;

  explicit TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}
  explicit TreeNode(T&& val)
      : value(std::move(val)), left(nullptr), right(nullptr) {}
};

template <class T>
class ITree {
 public:
  virtual ~ITree() = default;

  virtual void Add(const T& value) = 0;
  virtual void Remove(const T& value) = 0;
  virtual void Clear() = 0;
  virtual void PrintPreOrder() = 0;
  virtual void PrintInOrder() = 0;
  virtual void PrintPostOrder() = 0;
  virtual std::size_t Size() const = 0;
  virtual std::size_t Height() const = 0;
  virtual double AverageHeight() const = 0;
  virtual T Sum() const = 0;
};