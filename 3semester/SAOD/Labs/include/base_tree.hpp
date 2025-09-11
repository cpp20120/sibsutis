#pragma once

#include <print>
#include <vector>

#include "tree_types.hpp"

template <class T, class TNode = TreeNode<T>>
class BaseTree : public ITree<T> {
 protected:
  std::unique_ptr<TNode> root_;

  static void RemoveSubtree(std::unique_ptr<TNode>& node);
  static void PrintPreOrder(const std::unique_ptr<TNode>& node);
  static void PrintInOrder(const std::unique_ptr<TNode>& node);
  static void PrintPostOrder(const std::unique_ptr<TNode>& node);
  static std::size_t Size(const std::unique_ptr<TNode>& node);
  static std::size_t Height(const std::unique_ptr<TNode>& node);
  static std::size_t SumPathLengths(const std::unique_ptr<TNode>& node,
                                    std::size_t level);
  static T SumValues(const std::unique_ptr<TNode>& node);
  static void CollectInOrder(const std::unique_ptr<TNode>& node,
                             std::vector<T>& elements);
  static void CollectPreOrder(const std::unique_ptr<TNode>& node,
                              std::vector<T>& elements);
  void CopyTree(const std::unique_ptr<TNode>& src,
                std::unique_ptr<TNode>& dest);

 public:
  BaseTree();
  BaseTree(const BaseTree& other);
  BaseTree(BaseTree&& other) noexcept;
  BaseTree& operator=(const BaseTree& other);
  BaseTree& operator=(BaseTree&& other) noexcept;
  ~BaseTree() override = default;

  void Add(const T& value) override { AddImpl(value); }
  void Remove(const T& value) override { RemoveImpl(value); }
  void Clear() override;
  void PrintPreOrder() override;
  void PrintInOrder() override;
  void PrintPostOrder() override;
  std::size_t Size() const override;
  std::size_t Height() const override;
  double AverageHeight() const override;
  T Sum() const override;

  T Get(std::size_t index) const;
  std::vector<T> GetInOrderElements() const;
  std::vector<T> GetPreOrderElements() const;

 protected:
  virtual void AddImpl(const T& value) = 0;
  virtual void RemoveImpl(const T& value) = 0;
};