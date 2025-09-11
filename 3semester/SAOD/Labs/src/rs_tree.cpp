#include "rs_tree.hpp"

#include "os_tree.hpp"

template <class T, class TNode>
std::unique_ptr<TNode> RSTree<T, TNode>::AddRecursive(
    const T& value, std::unique_ptr<TNode> node) {
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

template <class T, class TNode>
void RSTree<T, TNode>::RemoveRightmost(std::unique_ptr<TNode>& current) {
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

template <class T, class TNode>
void RSTree<T, TNode>::RemoveLeftmost(std::unique_ptr<TNode>& current) {
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

template <class T, class TNode>
void RSTree<T, TNode>::RemoveRecursive(std::unique_ptr<TNode>& node,
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

template <class T, class TNode>
void RSTree<T, TNode>::AddImpl(const T& value) {
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

template <class T, class TNode>
void RSTree<T, TNode>::AddRecursive(const T& value) {
  this->root_ = AddRecursive(value, std::move(this->root_));
}

template <class T, class TNode>
void RSTree<T, TNode>::RemoveImpl(const T& value) {
  RemoveRecursive(this->root_, value);
}

template class RSTree<int>;
template class RSTree<double>;
template class RSTree<float>;

template class RSTree<int, OSTreeNode<int>>;
template class RSTree<double, OSTreeNode<double>>;
template class RSTree<float, OSTreeNode<float>>;