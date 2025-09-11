#pragma once

#include "base_tree.hpp"

template <class T>
struct AVLTreeNode {
  T value;
  std::unique_ptr<AVLTreeNode> left;
  std::unique_ptr<AVLTreeNode> right;
  int balance;

  explicit AVLTreeNode(const T& val)
      : value(val), left(nullptr), right(nullptr), balance(0) {}
};

template <class T>
class AVLTree : public BaseTree<T, AVLTreeNode<T>> {
 private:
  using NodePtr = std::unique_ptr<AVLTreeNode<T>>;

  NodePtr LeftLeftRotation(NodePtr node);
  NodePtr RightRightRotation(NodePtr node);
  NodePtr LeftRightRotation(NodePtr node);
  NodePtr RightLeftRotation(NodePtr node);

  NodePtr BalanceTree(NodePtr node);
  int GetHeight(const NodePtr& node) const;
  void UpdateBalance(NodePtr& node);

  NodePtr AddRecursive(const T& value, NodePtr node, bool& heightChanged);
  NodePtr RemoveRecursive(const T& value, NodePtr node, bool& heightChanged);
  NodePtr FindMin(NodePtr node) const;

  bool ContainsRecursive(const AVLTreeNode<T>* node, const T& value) const;

 public:
  using BaseTree<T, AVLTreeNode<T>>::BaseTree;

  void AddImpl(const T& value) override;
  void RemoveImpl(const T& value) override;

  bool Contains(const T& value) const;
};