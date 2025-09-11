#include "base_tree.hpp"

#include <stdexcept>

#include "avl_tree.hpp"
#include "os_tree.hpp"

template <class T, class TNode>
void BaseTree<T, TNode>::RemoveSubtree(std::unique_ptr<TNode>& node) {
  if (!node) return;
  RemoveSubtree(node->left);
  RemoveSubtree(node->right);
  node.reset();
}

template <class T, class TNode>
void BaseTree<T, TNode>::PrintPreOrder(const std::unique_ptr<TNode>& node) {
  if (!node) return;
  std::print("{} ", node->value);
  PrintPreOrder(node->left);
  PrintPreOrder(node->right);
}

template <class T, class TNode>
void BaseTree<T, TNode>::PrintInOrder(const std::unique_ptr<TNode>& node) {
  if (!node) return;
  PrintInOrder(node->left);
  std::print("{} ", node->value);
  PrintInOrder(node->right);
}

template <class T, class TNode>
void BaseTree<T, TNode>::PrintPostOrder(const std::unique_ptr<TNode>& node) {
  if (!node) return;
  PrintPostOrder(node->left);
  PrintPostOrder(node->right);
  std::print("{} ", node->value);
}

template <class T, class TNode>
std::size_t BaseTree<T, TNode>::Size(const std::unique_ptr<TNode>& node) {
  if (!node) return 0;
  return 1 + Size(node->left) + Size(node->right);
}

template <class T, class TNode>
std::size_t BaseTree<T, TNode>::Height(const std::unique_ptr<TNode>& node) {
  if (!node) return 0;
  return std::max(Height(node->left), Height(node->right)) + 1;
}

template <class T, class TNode>
std::size_t BaseTree<T, TNode>::SumPathLengths(
    const std::unique_ptr<TNode>& node, std::size_t level) {
  if (!node) return 0;
  return level + SumPathLengths(node->left, level + 1) +
         SumPathLengths(node->right, level + 1);
}

template <class T, class TNode>
T BaseTree<T, TNode>::SumValues(const std::unique_ptr<TNode>& node) {
  if (!node) return T{};
  return node->value + SumValues(node->left) + SumValues(node->right);
}

template <class T, class TNode>
void BaseTree<T, TNode>::CollectInOrder(const std::unique_ptr<TNode>& node,
                                        std::vector<T>& elements) {
  if (!node) return;
  CollectInOrder(node->left, elements);
  elements.push_back(node->value);
  CollectInOrder(node->right, elements);
}

template <class T, class TNode>
void BaseTree<T, TNode>::CollectPreOrder(const std::unique_ptr<TNode>& node,
                                         std::vector<T>& elements) {
  if (!node) return;
  elements.push_back(node->value);
  CollectPreOrder(node->left, elements);
  CollectPreOrder(node->right, elements);
}

template <class T, class TNode>
void BaseTree<T, TNode>::CopyTree(const std::unique_ptr<TNode>& src,
                                  std::unique_ptr<TNode>& dest) {
  if (!src) return;
  dest = std::make_unique<TNode>(src->value);
  CopyTree(src->left, dest->left);
  CopyTree(src->right, dest->right);
}

template <class T, class TNode>
BaseTree<T, TNode>::BaseTree() : root_(nullptr) {}

template <class T, class TNode>
BaseTree<T, TNode>::BaseTree(const BaseTree& other) {
  CopyTree(other.root_, root_);
}

template <class T, class TNode>
BaseTree<T, TNode>::BaseTree(BaseTree&& other) noexcept
    : root_(std::move(other.root_)) {}

template <class T, class TNode>
BaseTree<T, TNode>& BaseTree<T, TNode>::operator=(const BaseTree& other) {
  if (this != &other) {
    Clear();
    CopyTree(other.root_, root_);
  }
  return *this;
}

template <class T, class TNode>
BaseTree<T, TNode>& BaseTree<T, TNode>::operator=(BaseTree&& other) noexcept {
  if (this != &other) {
    root_ = std::move(other.root_);
  }
  return *this;
}

template <class T, class TNode>
void BaseTree<T, TNode>::Clear() {
  RemoveSubtree(root_);
}

template <class T, class TNode>
void BaseTree<T, TNode>::PrintPreOrder() {
  PrintPreOrder(root_);
  std::println();
}

template <class T, class TNode>
void BaseTree<T, TNode>::PrintInOrder() {
  PrintInOrder(root_);
  std::println();
}

template <class T, class TNode>
void BaseTree<T, TNode>::PrintPostOrder() {
  PrintPostOrder(root_);
  std::println();
}

template <class T, class TNode>
std::size_t BaseTree<T, TNode>::Size() const {
  return Size(root_);
}

template <class T, class TNode>
std::size_t BaseTree<T, TNode>::Height() const {
  return Height(root_);
}

template <class T, class TNode>
double BaseTree<T, TNode>::AverageHeight() const {
  const auto size = Size();
  if (size == 0) return 0.0;
  return static_cast<double>(SumPathLengths(root_, 1)) /
         static_cast<double>(size);
}

template <class T, class TNode>
T BaseTree<T, TNode>::Sum() const {
  return SumValues(root_);
}

template <class T, class TNode>
T BaseTree<T, TNode>::Get(std::size_t index) const {
  std::vector<T> elements;
  CollectInOrder(root_, elements);
  if (index >= elements.size()) {
    throw std::out_of_range("Index out of range");
  }
  return elements[index];
}

template <class T, class TNode>
std::vector<T> BaseTree<T, TNode>::GetInOrderElements() const {
  std::vector<T> elements;
  CollectInOrder(root_, elements);
  return elements;
}

template <class T, class TNode>
std::vector<T> BaseTree<T, TNode>::GetPreOrderElements() const {
  std::vector<T> elements;
  CollectPreOrder(root_, elements);
  return elements;
}

template class BaseTree<int>;
template class BaseTree<double>;
template class BaseTree<float>;

template class BaseTree<int, TreeNode<int>>;
template class BaseTree<double, TreeNode<double>>;
template class BaseTree<float, TreeNode<float>>;

template class BaseTree<int, AVLTreeNode<int>>;
template class BaseTree<double, AVLTreeNode<double>>;
template class BaseTree<float, AVLTreeNode<float>>;

template class BaseTree<int, OSTreeNode<int>>;
template class BaseTree<double, OSTreeNode<double>>;
template class BaseTree<float, OSTreeNode<float>>;
