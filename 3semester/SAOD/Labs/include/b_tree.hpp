#pragma once

#include <memory>
#include <print>
#include <stdexcept>
#include <vector>

#include "tree_types.hpp"

template <class T, std::size_t M = 3>
class BTree : public ITree<T> {
  static_assert(M >= 3, "B-tree order must be at least 3");

 private:
  struct BTreeNode {
    std::vector<T> values;
    std::vector<std::unique_ptr<BTreeNode>> children;

    BTreeNode() {
      values.reserve(M - 1);
      children.reserve(M);
    }

    BTreeNode(const BTreeNode&) = delete;
    BTreeNode& operator=(const BTreeNode&) = delete;
    BTreeNode(BTreeNode&& other) noexcept = default;
    BTreeNode& operator=(BTreeNode&& other) noexcept = default;

    bool IsLeaf() const { return children.empty(); }
    bool IsFull() const { return values.size() == M - 1; }

    std::size_t FindInsertPosition(const T& value) const {
      std::size_t pos = 0;
      while (pos < values.size() && value > values[pos]) {
        ++pos;
      }
      return pos;
    }
  };

  std::unique_ptr<BTreeNode> root_;
  std::size_t size_;

  void SplitChild(BTreeNode* parent, std::size_t childIndex);
  void InsertNonFull(BTreeNode* node, const T& value);
  void PrintPreOrder(const BTreeNode* node) const;
  void PrintInOrder(const BTreeNode* node) const;
  void PrintPostOrder(const BTreeNode* node) const;
  void ClearSubtree(std::unique_ptr<BTreeNode>& node);
  std::size_t CountNodes(const BTreeNode* node) const;
  bool ContainsRecursive(const BTreeNode* node, const T& value) const;
  std::size_t CalculateHeight(const BTreeNode* node) const;
  T SumValues(const BTreeNode* node) const;
  void RemoveFromNode(BTreeNode* node, const T& value, bool& removed);
  void RemoveFromInternalNode(BTreeNode* node, std::size_t pos);
  void BalanceNode(BTreeNode* node, std::size_t childIndex);
  void BorrowFromLeft(BTreeNode* parent, std::size_t childIndex);
  void BorrowFromRight(BTreeNode* parent, std::size_t childIndex);
  void MergeWithLeftSibling(BTreeNode* parent, std::size_t childIndex);
  void MergeWithRightSibling(BTreeNode* parent, std::size_t childIndex);

 public:
  BTree();
  ~BTree() override = default;

  BTree(const BTree&) = delete;
  BTree& operator=(const BTree&) = delete;

  BTree(BTree&&) noexcept = default;
  BTree& operator=(BTree&&) noexcept = default;

  void Add(const T& value) override;
  void Remove(const T& value) override;
  void Clear() override;
  void PrintPreOrder() override;
  void PrintInOrder() override;
  void PrintPostOrder() override;
  std::size_t Size() const override;
  std::size_t Height() const override;
  double AverageHeight() const override;
  T Sum() const override;
  bool Contains(const T& value) const;
};