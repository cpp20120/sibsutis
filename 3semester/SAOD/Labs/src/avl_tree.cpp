#include "avl_tree.hpp"

#include <algorithm>

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::LeftLeftRotation(NodePtr node) {
  auto newRoot = std::move(node->left);
  node->left = std::move(newRoot->right);
  newRoot->right = std::move(node);

  UpdateBalance(newRoot->right);
  UpdateBalance(newRoot);

  return newRoot;
}

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::RightRightRotation(NodePtr node) {
  auto newRoot = std::move(node->right);
  node->right = std::move(newRoot->left);
  newRoot->left = std::move(node);

  UpdateBalance(newRoot->left);
  UpdateBalance(newRoot);

  return newRoot;
}

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::LeftRightRotation(NodePtr node) {
  node->left = RightRightRotation(std::move(node->left));
  return LeftLeftRotation(std::move(node));
}

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::RightLeftRotation(NodePtr node) {
  node->right = LeftLeftRotation(std::move(node->right));
  return RightRightRotation(std::move(node));
}

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::BalanceTree(NodePtr node) {
  UpdateBalance(node);

  if (node->balance > 1) {
    if (node->left->balance >= 0) {
      return LeftLeftRotation(std::move(node));
    } else {
      return LeftRightRotation(std::move(node));
    }
  }

  if (node->balance < -1) {
    if (node->right->balance <= 0) {
      return RightRightRotation(std::move(node));
    } else {
      return RightLeftRotation(std::move(node));
    }
  }

  return node;
}

template <class T>
int AVLTree<T>::GetHeight(const NodePtr& node) const {
  if (!node) return 0;
  return 1 + std::max(GetHeight(node->left), GetHeight(node->right));
}

template <class T>
void AVLTree<T>::UpdateBalance(NodePtr& node) {
  if (!node) return;
  node->balance = GetHeight(node->left) - GetHeight(node->right);
}

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::AddRecursive(const T& value,
                                                      NodePtr node,
                                                      bool& heightChanged) {
  if (!node) {
    heightChanged = true;
    return std::make_unique<AVLTreeNode<T>>(value);
  }

  if (value < node->value) {
    node->left = AddRecursive(value, std::move(node->left), heightChanged);
  } else if (value > node->value) {
    node->right = AddRecursive(value, std::move(node->right), heightChanged);
  } else {
    heightChanged = false;
    return node;
  }

  if (heightChanged) {
    node = BalanceTree(std::move(node));
    heightChanged = (std::abs(node->balance) > 1);
  }

  return node;
}

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::FindMin(NodePtr node) const {
  while (node->left) {
    node = std::move(node->left);
  }
  return node;
}

template <class T>
typename AVLTree<T>::NodePtr AVLTree<T>::RemoveRecursive(const T& value,
                                                         NodePtr node,
                                                         bool& heightChanged) {
  if (!node) {
    heightChanged = false;
    return nullptr;
  }

  if (value < node->value) {
    node->left = RemoveRecursive(value, std::move(node->left), heightChanged);
  } else if (value > node->value) {
    node->right = RemoveRecursive(value, std::move(node->right), heightChanged);
  } else {
    if (!node->left || !node->right) {
      heightChanged = true;
      return node->left ? std::move(node->left) : std::move(node->right);
    }

    auto successor = FindMin(std::move(node->right));
    node->value = successor->value;
    node->right = RemoveRecursive(successor->value, std::move(node->right),
                                  heightChanged);
  }

  if (heightChanged) {
    node = BalanceTree(std::move(node));
    heightChanged = (std::abs(node->balance) > 1);
  }

  return node;
}

template <class T>
bool AVLTree<T>::ContainsRecursive(const AVLTreeNode<T>* node,
                                   const T& value) const {
  if (!node) return false;

  if (value == node->value) {
    return true;
  } else if (value < node->value) {
    return ContainsRecursive(node->left.get(), value);
  } else {
    return ContainsRecursive(node->right.get(), value);
  }
}

template <class T>
bool AVLTree<T>::Contains(const T& value) const {
  return ContainsRecursive(this->root_.get(), value);
}

template <class T>
void AVLTree<T>::AddImpl(const T& value) {
  bool heightChanged = false;
  this->root_ = AddRecursive(value, std::move(this->root_), heightChanged);
}

template <class T>
void AVLTree<T>::RemoveImpl(const T& value) {
  bool heightChanged = false;
  this->root_ = RemoveRecursive(value, std::move(this->root_), heightChanged);
}

template class AVLTree<int>;
template class AVLTree<double>;
template class AVLTree<float>;