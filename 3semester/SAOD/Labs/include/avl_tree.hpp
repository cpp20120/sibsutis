#pragma once

#include <algorithm>
#include <memory>
#include <iostream>

#include "./base_tree.hpp"

template <class T>
struct AVLTreeNode {
  T value;
  std::unique_ptr<AVLTreeNode> left;
  std::unique_ptr<AVLTreeNode> right;
  int height;

  explicit AVLTreeNode(const T& val)
      : value(val), left(nullptr), right(nullptr), height(1) {}
  explicit AVLTreeNode(T&& val)
      : value(std::move(val)), left(nullptr), right(nullptr), height(1) {}
};

template <class T>
class AVLTree : public BaseTree<T, AVLTreeNode<T>> {
 private:
  using NodePtr = std::unique_ptr<AVLTreeNode<T>>;

  // Height and balance utilities
  int GetHeight(const NodePtr& node) const {
    return node ? node->height : 0;
  }

  int GetBalance(const NodePtr& node) const {
    return node ? GetHeight(node->left) - GetHeight(node->right) : 0;
  }

  void UpdateHeight(NodePtr& node) {
    if (node) {
      node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
    }
  }

  // Rotations
  NodePtr RotateRight(NodePtr y) {
    auto x = std::move(y->left);
    y->left = std::move(x->right);
    x->right = std::move(y);

    UpdateHeight(x->right);
    UpdateHeight(x);

    return x;
  }

  NodePtr RotateLeft(NodePtr x) {
    auto y = std::move(x->right);
    x->right = std::move(y->left);
    y->left = std::move(x);

    UpdateHeight(y->left);
    UpdateHeight(y);

    return y;
  }

  // Balancing
  NodePtr BalanceTree(NodePtr node) {
    if (!node) return node;

    UpdateHeight(node);
    int balance = GetBalance(node);

    if (balance > 1) {
      if (GetBalance(node->left) >= 0) {
        return RotateRight(std::move(node));
      } else {
        node->left = RotateLeft(std::move(node->left));
        return RotateRight(std::move(node));
      }
    }

    if (balance < -1) {
      if (GetBalance(node->right) <= 0) {
        return RotateLeft(std::move(node));
      } else {
        node->right = RotateRight(std::move(node->right));
        return RotateLeft(std::move(node));
      }
    }

    return node;
  }

  // Recursive operations
  NodePtr AddRecursive(const T& value, NodePtr node) {
    if (!node) {
      return std::make_unique<AVLTreeNode<T>>(value);
    }

    if (value < node->value) {
      node->left = AddRecursive(value, std::move(node->left));
    } else {
      node->right = AddRecursive(value, std::move(node->right));
    }

    return BalanceTree(std::move(node));
  }

  NodePtr FindMin(NodePtr node) const {
    while (node && node->left) {
      node = std::move(node->left);
    }
    return node;
  }

  NodePtr RemoveRecursive(const T& value, NodePtr node) {
    if (!node) {
      return nullptr;
    }

    if (value < node->value) {
      node->left = RemoveRecursive(value, std::move(node->left));
    } else if (value > node->value) {
      node->right = RemoveRecursive(value, std::move(node->right));
    } else {
      if (!node->left || !node->right) {
        return node->left ? std::move(node->left) : std::move(node->right);
      } else {
        auto successor = FindMin(std::move(node->right));
        node->value = successor->value;
        node->right = RemoveRecursive(successor->value, std::move(node->right));
      }
    }

    return BalanceTree(std::move(node));
  }

  // Search
  bool ContainsRecursive(const AVLTreeNode<T>* node, const T& value) const {
    if (!node) return false;

    if (value == node->value) {
      return true;
    } else if (value < node->value) {
      return ContainsRecursive(node->left.get(), value);
    } else {
      return ContainsRecursive(node->right.get(), value);
    }
  }

  // Balance checking
  int CheckHeightAndBalance(const AVLTreeNode<T>* node, bool& balanced) const {
    if (!node) return 0;

    int leftHeight = CheckHeightAndBalance(node->left.get(), balanced);
    int rightHeight = CheckHeightAndBalance(node->right.get(), balanced);

    int currentBalance = leftHeight - rightHeight;

    if (std::abs(currentBalance) > 1) {
      balanced = false;
    }

    return std::max(leftHeight, rightHeight) + 1;
  }

  bool IsBalancedRecursive(const AVLTreeNode<T>* node) const {
    if (!node) return true;

    bool balanced = true;
    CheckHeightAndBalance(node, balanced);
    return balanced;
  }

 public:
  using BaseTree<T, AVLTreeNode<T>>::BaseTree;

  void AddImpl(const T& value) override {
    this->root_ = AddRecursive(value, std::move(this->root_));
  }

  void RemoveImpl(const T& value) override {
    this->root_ = RemoveRecursive(value, std::move(this->root_));
  }

  bool Contains(const T& value) const {
    return ContainsRecursive(this->root_.get(), value);
  }

  // Additional AVL-specific methods
  bool IsBalanced() const {
    return IsBalancedRecursive(this->root_.get());
  }

  int GetBalance() const {
    if (!this->root_) return 0;

    int leftHeight = this->root_->left ? this->root_->left->height : 0;
    int rightHeight = this->root_->right ? this->root_->right->height : 0;
    return leftHeight - rightHeight;
  }

  // For debugging
  void PrintBalanceInfoRecursive(const AVLTreeNode<T>* node,
                                 int depth = 0) const {
    if (!node) return;

    PrintBalanceInfoRecursive(node->right.get(), depth + 1);

    for (int i = 0; i < depth; ++i) std::cout << "   ";

    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    int balance = leftHeight - rightHeight;

    std::cout << node->value << " (h:" << node->height << ", b:" << balance
              << ")\n";

    PrintBalanceInfoRecursive(node->left.get(), depth + 1);
  }

  void PrintBalanceInfo() const {
    std::cout << "Tree balance information:\n";
    PrintBalanceInfoRecursive(this->root_.get());
    std::cout << "Overall balanced: " << (IsBalanced() ? "Yes" : "No") << "\n";
  }
};