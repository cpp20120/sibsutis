#pragma once

#include <algorithm>
#include <memory>
#include <stack>
#include <type_traits>
#include <vector>

#include "./base_tree.hpp"

template <class T, class TNode = TreeNode<T>>
class PBSTree : public BaseTree<T, TNode> {
 private:
  std::unique_ptr<TNode> BuildBalancedTree(
      int64_t left, int64_t right, const std::vector<T>& sorted_elements) {
    if (left > right) return nullptr;

    const std::size_t mid = (left + right) / 2;
    auto node = std::make_unique<TNode>(sorted_elements[mid]);

    node->left = BuildBalancedTree(left, mid - 1, sorted_elements);
    node->right = BuildBalancedTree(mid + 1, right, sorted_elements);

    return node;
  }

 public:
  PBSTree() = default;

  template <typename Container>
  explicit PBSTree(Container&& elements) {
    static_assert(std::is_constructible_v<std::vector<T>, Container&&>,
                  "Container must be convertible to std::vector<T>");

    std::vector<T> sorted(std::forward<Container>(elements));
    std::sort(sorted.begin(), sorted.end());
    this->root_ = BuildBalancedTree(0, sorted.size() - 1, sorted);
  }

  void AddImpl(const T& value) override {
    std::vector<T> elements;
    this->CollectInOrder(this->root_, elements);
    elements.push_back(value);
    std::sort(elements.begin(), elements.end());
    this->Clear();
    this->root_ = BuildBalancedTree(0, elements.size() - 1, elements);
  }

  void RemoveImpl(const T& value) override {
    std::vector<T> elements;
    this->CollectInOrder(this->root_, elements);

    auto it = std::find(elements.begin(), elements.end(), value);
    if (it != elements.end()) {
      elements.erase(it);
    }

    this->Clear();
    if (!elements.empty()) {
      this->root_ = BuildBalancedTree(0, elements.size() - 1, elements);
    }
  }

  TNode* SearchImpl(TNode* node, const T& value) const {
    if (!node) return nullptr;

    if (value == node->value) {
      return node;
    } else if (value < node->value) {
      return SearchImpl(node->left.get(), value);
    } else {
      return SearchImpl(node->right.get(), value);
    }
  }

  TNode* Search(const T& value) const {
    return SearchImpl(this->root_.get(), value);
  }

  bool Contains(const T& value) const { return Search(value) != nullptr; }

  std::vector<T> ToVector() const { return this->GetInOrderElements(); }

  bool Empty() const { return this->root_ == nullptr; }
};