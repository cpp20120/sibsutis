#pragma once

#include "./base_tree.hpp"

template <class T, class TNode = TreeNode<T>>
class RSTree : public BaseTree<T, TNode> {
 protected:
  std::unique_ptr<TNode> AddRecursive(const T& value,
                                      std::unique_ptr<TNode> node) {
    if (!node) {
      return std::make_unique<TNode>(value);
    }

    if (value < node->value) {
      node->left = AddRecursive(value, std::move(node->left));
    } else {
      node->right = AddRecursive(value, std::move(node->right));
    }
    return node;
  }

  void RemoveRightmost(std::unique_ptr<TNode>& current) {
    auto* parent = current.get();
    auto* rightmost = current->right.get();

    while (rightmost->left) {
      parent = rightmost;
      rightmost = rightmost->left.get();
    }

    current->value = std::move(rightmost->value);

    if (parent == current.get()) {
      parent->right = std::move(rightmost->right);
    } else {
      parent->left = std::move(rightmost->left);
    }
  }

  void RemoveLeftmost(std::unique_ptr<TNode>& current) {
    auto* parent = current.get();
    auto* leftmost = current->left.get();

    while (leftmost->right) {
      parent = leftmost;
      leftmost = leftmost->right.get();
    }

    current->value = std::move(leftmost->value);

    if (parent == current.get()) {
      parent->left = std::move(leftmost->left);
    } else {
      parent->right = std::move(leftmost->right);
    }
  }

  void RemoveRecursive(std::unique_ptr<TNode>& node,
                                       const T& value) {
    if (!node) return;

    if (node->value == value) {
      if (!node->left && !node->right) {
        node.reset();
      } else if (node->right) {
        RemoveRightmost(node);
      } else {
        RemoveLeftmost(node);
      }
    } else if (value < node->value) {
      RemoveRecursive(node->left, value);
    } else {
      RemoveRecursive(node->right, value);
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

 public:
  using BaseTree<T, TNode>::BaseTree;

  void AddImpl(const T& value) override {
    if (!this->root_) {
      this->root_ = std::make_unique<TNode>(value);
      return;
    }

    auto* current = this->root_.get();
    auto* parent = current;

    while (current) {
      parent = current;
      if (value < current->value) {
        current = current->left.get();
      } else {
        current = current->right.get();
      }
    }

    if (value < parent->value) {
      parent->left = std::make_unique<TNode>(value);
    } else {
      parent->right = std::make_unique<TNode>(value);
    }
  }

  void AddRecursive(const T& value) {
    this->root_ = AddRecursive(value, std::move(this->root_));
  }

  void RemoveImpl(const T& value) override {
    RemoveRecursive(this->root_, value);
  }

  bool Contains(const T& value) const {
    return SearchImpl(this->root_.get(), value) != nullptr;
  }

  std::vector<T> GetInOrderElements() const {
    return this->BaseTree<T, TNode>::GetInOrderElements();
  }

  std::vector<T> ToVector() const {
    return GetInOrderElements();
  }

  bool Empty() const {
    return this->root_ == nullptr;
  }

  TNode* GetRoot() const {
    return this->root_.get();
  }
};