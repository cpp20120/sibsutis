#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "base_tree.hpp"

template <class T, class TNode = TreeNode<T>>
class PBSTree : public BaseTree<T, TNode> {
 private:
  std::unique_ptr<TNode> BuildBalancedTree(
      int64_t left, int64_t right, const std::vector<T> &sorted_elements);
  std::size_t size_;

 public:
  PBSTree() = default;
  explicit PBSTree(const std::vector<T> &values);
  void AddImpl(const T &value) override;
  void RemoveImpl(const T &value) override;
};

template <class T, class TNode>
std::unique_ptr<TNode> PBSTree<T, TNode>::BuildBalancedTree(
    int64_t left, int64_t right, const std::vector<T> &sorted_elements) {
  if (left > right) return nullptr;

  const std::size_t mid = (left + right) / 2;
  auto node = std::make_unique<TNode>(sorted_elements[mid]);

  node->left = BuildBalancedTree(left, mid - 1, sorted_elements);
  node->right = BuildBalancedTree(mid + 1, right, sorted_elements);

  return node;
}

template <class T, class TNode>
PBSTree<T, TNode>::PBSTree(const std::vector<T> &values) {
  std::vector<T> sorted = values;
  std::sort(sorted.begin(), sorted.end());
  this->root_ = BuildBalancedTree(0, sorted.size() - 1, sorted);
  this->size_ = values.size();
}

template <class T, class TNode>
void PBSTree<T, TNode>::AddImpl(const T &value) {
  std::vector<T> elements;
  this->CollectInOrder(this->root_, elements);
  elements.push_back(value);
  std::sort(elements.begin(), elements.end());
  this->Clear();
  this->root_ = BuildBalancedTree(0, elements.size() - 1, elements);
}

template <class T, class TNode>
void PBSTree<T, TNode>::RemoveImpl(const T &value) {
  std::vector<T> elements;
  this->CollectInOrder(this->root_, elements);
  auto it = std::find(elements.begin(), elements.end(), value);
  if (it != elements.end()) {
    elements.erase(it);
  }
  this->Clear();
  this->root_ = BuildBalancedTree(0, elements.size() - 1, elements);
}
