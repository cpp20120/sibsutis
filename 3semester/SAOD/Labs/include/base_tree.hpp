#pragma once

#include <print>
#include <stdexcept>
#include <vector>

#include "./tree_types.hpp"

template <class T, class TNode = TreeNode<T>>
class BaseTree : public ITree<T> {
 protected:
  std::unique_ptr<TNode> root_;

  static void RemoveSubtree(std::unique_ptr<TNode>& node) {
    if (!node) return;
    RemoveSubtree(node->left);
    RemoveSubtree(node->right);
    node.reset();
  }

  static void PrintPreOrder(const std::unique_ptr<TNode>& node) {
    if (!node) return;
    std::print("{} ", node->value);
    PrintPreOrder(node->left);
    PrintPreOrder(node->right);
  }

  static void PrintInOrder(const std::unique_ptr<TNode>& node) {
    if (!node) return;
    PrintInOrder(node->left);
    std::print("{} ", node->value);
    PrintInOrder(node->right);
  }

  static void PrintPostOrder(const std::unique_ptr<TNode>& node) {
    if (!node) return;
    PrintPostOrder(node->left);
    PrintPostOrder(node->right);
    std::print("{} ", node->value);
  }

  static std::size_t Size(const std::unique_ptr<TNode>& node) {
    if (!node) return 0;
    return 1 + Size(node->left) + Size(node->right);
  }

  static std::size_t Height(const std::unique_ptr<TNode>& node) {
    if (!node) return 0;
    return std::max(Height(node->left), Height(node->right)) + 1;
  }

  static std::size_t SumPathLengths(const std::unique_ptr<TNode>& node,
                                    std::size_t level) {
    if (!node) return 0;
    return (level + 1) + SumPathLengths(node->left, level + 1) +
           SumPathLengths(node->right, level + 1);
  }

  static T SumValues(const std::unique_ptr<TNode>& node) {
    if (!node) return T{};
    return node->value + SumValues(node->left) + SumValues(node->right);
  }

  static void CollectInOrder(const std::unique_ptr<TNode>& node,
                             std::vector<T>& elements) {
    if (!node) return;
    CollectInOrder(node->left, elements);
    elements.push_back(node->value);
    CollectInOrder(node->right, elements);
  }

  static void CollectPreOrder(const std::unique_ptr<TNode>& node,
                              std::vector<T>& elements) {
    if (!node) return;
    elements.push_back(node->value);
    CollectPreOrder(node->left, elements);
    CollectPreOrder(node->right, elements);
  }

  static void CopyTree(const std::unique_ptr<TNode>& src,
                       std::unique_ptr<TNode>& dest) {
    if (!src) return;
    dest = std::make_unique<TNode>(src->value);
    CopyTree(src->left, dest->left);
    CopyTree(src->right, dest->right);
  }

 public:
  BaseTree() : root_(nullptr) {}
  BaseTree(const BaseTree& other) { CopyTree(other.root_, root_); }
  BaseTree(BaseTree&& other) noexcept : root_(std::move(other.root_)) {}

  BaseTree& operator=(const BaseTree& other) {
    if (this != &other) {
      Clear();
      CopyTree(other.root_, root_);
    }
    return *this;
  }

  BaseTree& operator=(BaseTree&& other) noexcept {
    if (this != &other) {
      root_ = std::move(other.root_);
    }
    return *this;
  }

  ~BaseTree() override = default;

  void Add(const T& value) override { AddImpl(value); }
  void Remove(const T& value) override { RemoveImpl(value); }

  void Clear() override { RemoveSubtree(root_); }

  void PrintPreOrder() override {
    PrintPreOrder(root_);
    std::println();
  }

  void PrintInOrder() override {
    PrintInOrder(root_);
    std::println();
  }

  void PrintPostOrder() override {
    PrintPostOrder(root_);
    std::println();
  }

  std::size_t Size() const override { return Size(root_); }

  std::size_t Height() const override { return Height(root_); }

  double AverageHeight() const override {
    const auto size = Size();
    if (size == 0) return 0.0;
    return static_cast<double>(SumPathLengths(root_, 0)) /
           static_cast<double>(size);
  }

  T Sum() const override { return SumValues(root_); }

  T Get(std::size_t index) const {
    std::vector<T> elements;
    CollectInOrder(root_, elements);
    if (index >= elements.size()) {
      throw std::out_of_range("Index out of range");
    }
    return elements[index];
  }

  std::vector<T> GetInOrderElements() const {
    std::vector<T> elements;
    CollectInOrder(root_, elements);
    return elements;
  }

  std::vector<T> GetPreOrderElements() const {
    std::vector<T> elements;
    CollectPreOrder(root_, elements);
    return elements;
  }

 protected:
  virtual void AddImpl(const T& value) = 0;
  virtual void RemoveImpl(const T& value) = 0;
};