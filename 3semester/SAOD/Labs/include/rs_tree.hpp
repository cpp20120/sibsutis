#pragma once

#include "base_tree.hpp"

template <class T, class TNode = TreeNode<T>>
class RSTree : public BaseTree<T, TNode> {
 protected:
  std::unique_ptr<TNode> AddRecursive(const T& value,
                                      std::unique_ptr<TNode> node);
  void RemoveRightmost(std::unique_ptr<TNode>& current);
  void RemoveLeftmost(std::unique_ptr<TNode>& current);
  void RemoveRecursive(std::unique_ptr<TNode>& node, const T& value);

 public:
  using BaseTree<T, TNode>::BaseTree;

  void AddImpl(const T& value) override;
  void RemoveImpl(const T& value) override;

  void AddRecursive(const T& value);
};