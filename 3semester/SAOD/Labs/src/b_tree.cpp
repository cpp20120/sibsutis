#include "b_tree.hpp"

template <class T, std::size_t M>
BTree<T, M>::BTree() : root_(nullptr), size_(0) {}

template <class T, std::size_t M>
void BTree<T, M>::SplitChild(BTreeNode* parent, std::size_t childIndex) {
  auto& child = parent->children[childIndex];
  auto newChild = std::make_unique<BTreeNode>();

  const std::size_t midIndex = M / 2;
  T middleValue = std::move(child->values[midIndex]);

  newChild->values.assign(
      std::make_move_iterator(child->values.begin() + midIndex + 1),
      std::make_move_iterator(child->values.end()));
  child->values.resize(midIndex);

  if (!child->IsLeaf()) {
    newChild->children.assign(
        std::make_move_iterator(child->children.begin() + midIndex + 1),
        std::make_move_iterator(child->children.end()));
    child->children.resize(midIndex + 1);
  }

  auto insertPos = parent->FindInsertPosition(middleValue);
  parent->values.insert(parent->values.begin() + insertPos,
                        std::move(middleValue));
  parent->children.insert(parent->children.begin() + insertPos + 1,
                          std::move(newChild));
}

template <class T, std::size_t M>
void BTree<T, M>::InsertNonFull(BTreeNode* node, const T& value) {
  if (node->IsLeaf()) {
    auto pos = node->FindInsertPosition(value);
    node->values.insert(node->values.begin() + pos, value);
    return;
  }

  auto pos = node->FindInsertPosition(value);
  if (node->children[pos]->IsFull()) {
    SplitChild(node, pos);
    if (value > node->values[pos]) {
      ++pos;
    }
  }
  InsertNonFull(node->children[pos].get(), value);
}

template <class T, std::size_t M>
void BTree<T, M>::Add(const T& value) {
  if (!root_) {
    root_ = std::make_unique<BTreeNode>();
    root_->values.push_back(value);
    ++size_;
    return;
  }

  if (root_->IsFull()) {
    auto newRoot = std::make_unique<BTreeNode>();
    newRoot->children.push_back(std::move(root_));
    root_ = std::move(newRoot);
    SplitChild(root_.get(), 0);
  }

  InsertNonFull(root_.get(), value);
  ++size_;
}

template <class T, std::size_t M>
void BTree<T, M>::Remove(const T& value) {
  if (!root_) return;

  bool removed = false;
  RemoveFromNode(root_.get(), value, removed);

  if (removed) {
    size_--;

    if (root_->values.empty() && !root_->children.empty()) {
      root_ = std::move(root_->children[0]);
    }
  }
}

template <class T, std::size_t M>
void BTree<T, M>::RemoveFromNode(BTreeNode* node, const T& value,
                                 bool& removed) {
  if (!node) return;

  std::size_t pos = 0;
  while (pos < node->values.size() && value > node->values[pos]) {
    pos++;
  }

  if (pos < node->values.size() && node->values[pos] == value) {
    if (node->IsLeaf()) {
      node->values.erase(node->values.begin() + pos);
      removed = true;
    } else {
      RemoveFromInternalNode(node, pos);
      removed = true;
    }
  } else if (!node->IsLeaf()) {
    RemoveFromNode(node->children[pos].get(), value, removed);

    if (removed) {
      BalanceNode(node, pos);
    }
  }
}

template <class T, std::size_t M>
void BTree<T, M>::RemoveFromInternalNode(BTreeNode* node, std::size_t pos) {
  BTreeNode* current = node->children[pos].get();
  while (!current->IsLeaf()) {
    current = current->children.back().get();
  }

  T predecessor = current->values.back();
  node->values[pos] = predecessor;

  bool removed = false;
  RemoveFromNode(node->children[pos].get(), predecessor, removed);

  if (removed) {
    BalanceNode(node, pos);
  }
}

template <class T, std::size_t M>
void BTree<T, M>::BalanceNode(BTreeNode* node, std::size_t childIndex) {
  BTreeNode* child = node->children[childIndex].get();

  if (child->values.size() >= (M - 1) / 2) {
    return;
  }

  if (childIndex > 0) {
    BTreeNode* leftSibling = node->children[childIndex - 1].get();
    if (leftSibling->values.size() > (M - 1) / 2) {
      BorrowFromLeft(node, childIndex);
      return;
    }
  }

  if (childIndex < node->children.size() - 1) {
    BTreeNode* rightSibling = node->children[childIndex + 1].get();
    if (rightSibling->values.size() > (M - 1) / 2) {
      BorrowFromRight(node, childIndex);
      return;
    }
  }

  if (childIndex > 0) {
    MergeWithLeftSibling(node, childIndex);
  } else {
    MergeWithRightSibling(node, childIndex);
  }
}

template <class T, std::size_t M>
void BTree<T, M>::BorrowFromLeft(BTreeNode* parent, std::size_t childIndex) {
  BTreeNode* child = parent->children[childIndex].get();
  BTreeNode* leftSibling = parent->children[childIndex - 1].get();

  child->values.insert(child->values.begin(), parent->values[childIndex - 1]);

  parent->values[childIndex - 1] = leftSibling->values.back();
  leftSibling->values.pop_back();

  if (!leftSibling->IsLeaf()) {
    child->children.insert(child->children.begin(),
                           std::move(leftSibling->children.back()));
    leftSibling->children.pop_back();
  }
}

template <class T, std::size_t M>
void BTree<T, M>::BorrowFromRight(BTreeNode* parent, std::size_t childIndex) {
  BTreeNode* child = parent->children[childIndex].get();
  BTreeNode* rightSibling = parent->children[childIndex + 1].get();

  child->values.push_back(parent->values[childIndex]);

  parent->values[childIndex] = rightSibling->values.front();
  rightSibling->values.erase(rightSibling->values.begin());

  if (!rightSibling->IsLeaf()) {
    child->children.push_back(std::move(rightSibling->children.front()));
    rightSibling->children.erase(rightSibling->children.begin());
  }
}

template <class T, std::size_t M>
void BTree<T, M>::MergeWithLeftSibling(BTreeNode* parent,
                                       std::size_t childIndex) {
  BTreeNode* child = parent->children[childIndex].get();
  BTreeNode* leftSibling = parent->children[childIndex - 1].get();

  leftSibling->values.push_back(parent->values[childIndex - 1]);

  leftSibling->values.insert(leftSibling->values.end(), child->values.begin(),
                             child->values.end());

  if (!child->IsLeaf()) {
    leftSibling->children.insert(
        leftSibling->children.end(),
        std::make_move_iterator(child->children.begin()),
        std::make_move_iterator(child->children.end()));
  }

  parent->values.erase(parent->values.begin() + childIndex - 1);
  parent->children.erase(parent->children.begin() + childIndex);
}

template <class T, std::size_t M>
void BTree<T, M>::MergeWithRightSibling(BTreeNode* parent,
                                        std::size_t childIndex) {
  BTreeNode* child = parent->children[childIndex].get();
  BTreeNode* rightSibling = parent->children[childIndex + 1].get();

  child->values.push_back(parent->values[childIndex]);

  child->values.insert(child->values.end(), rightSibling->values.begin(),
                       rightSibling->values.end());

  if (!rightSibling->IsLeaf()) {
    child->children.insert(
        child->children.end(),
        std::make_move_iterator(rightSibling->children.begin()),
        std::make_move_iterator(rightSibling->children.end()));
  }

  parent->values.erase(parent->values.begin() + childIndex);
  parent->children.erase(parent->children.begin() + childIndex + 1);
}

template <class T, std::size_t M>
bool BTree<T, M>::ContainsRecursive(const BTreeNode* node,
                                    const T& value) const {
  if (!node) return false;

  std::size_t pos = 0;
  while (pos < node->values.size() && value > node->values[pos]) {
    pos++;
  }

  if (pos < node->values.size() && node->values[pos] == value) {
    return true;
  }

  if (!node->IsLeaf()) {
    return ContainsRecursive(node->children[pos].get(), value);
  }

  return false;
}

template <class T, std::size_t M>
void BTree<T, M>::Clear() {
  ClearSubtree(root_);
  size_ = 0;
}

template <class T, std::size_t M>
void BTree<T, M>::ClearSubtree(std::unique_ptr<BTreeNode>& node) {
  if (!node) return;
  for (auto& child : node->children) {
    ClearSubtree(child);
  }
  node.reset();
}

template <class T, std::size_t M>
void BTree<T, M>::PrintPreOrder() {
  PrintPreOrder(root_.get());
  std::println();
}

template <class T, std::size_t M>
void BTree<T, M>::PrintPreOrder(const BTreeNode* node) const {
  if (!node) return;

  for (std::size_t i = 0; i < node->values.size(); ++i) {
    std::print("{} ", node->values[i]);
    if (i < node->children.size()) {
      PrintPreOrder(node->children[i].get());
    }
  }
  if (!node->children.empty()) {
    PrintPreOrder(node->children.back().get());
  }
}

template <class T, std::size_t M>
void BTree<T, M>::PrintInOrder() {
  PrintInOrder(root_.get());
  std::println();
}

template <class T, std::size_t M>
void BTree<T, M>::PrintInOrder(const BTreeNode* node) const {
  if (!node) return;

  for (std::size_t i = 0; i < node->values.size(); ++i) {
    if (i < node->children.size()) {
      PrintInOrder(node->children[i].get());
    }
    std::print("{} ", node->values[i]);
  }
  if (!node->children.empty()) {
    PrintInOrder(node->children.back().get());
  }
}

template <class T, std::size_t M>
void BTree<T, M>::PrintPostOrder() {
  PrintPostOrder(root_.get());
  std::println();
}

template <class T, std::size_t M>
void BTree<T, M>::PrintPostOrder(const BTreeNode* node) const {
  if (!node) return;

  for (const auto& child : node->children) {
    PrintPostOrder(child.get());
  }
  for (const auto& value : node->values) {
    std::print("{} ", value);
  }
}

template <class T, std::size_t M>
std::size_t BTree<T, M>::Size() const {
  return size_;
}

template <class T, std::size_t M>
bool BTree<T, M>::Contains(const T& value) const {
  return ContainsRecursive(root_.get(), value);
}

template <class T, std::size_t M>
std::size_t BTree<T, M>::Height() const {
  return CalculateHeight(root_.get());
}

template <class T, std::size_t M>
std::size_t BTree<T, M>::CalculateHeight(const BTreeNode* node) const {
  if (!node) return 0;
  if (node->IsLeaf()) return 1;
  return 1 + CalculateHeight(node->children[0].get());
}

template <class T, std::size_t M>
double BTree<T, M>::AverageHeight() const {
  if (size_ == 0) return 0.0;
  return static_cast<double>(Height());
}

template <class T, std::size_t M>
T BTree<T, M>::Sum() const {
  return SumValues(root_.get());
}

template <class T, std::size_t M>
T BTree<T, M>::SumValues(const BTreeNode* node) const {
  if (!node) return T{};

  T sum{};
  for (const auto& value : node->values) {
    sum += value;
  }
  for (const auto& child : node->children) {
    sum += SumValues(child.get());
  }
  return sum;
}

template class BTree<int, 3>;
template class BTree<double, 3>;
template class BTree<float, 3>;