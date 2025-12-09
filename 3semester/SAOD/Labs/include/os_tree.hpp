#pragma once

#include <algorithm>
#include <print>
#include <unordered_map>
#include <utility>
#include <vector>

#include "./rs_tree.hpp"

template <class T>
struct OSTreeNode {
  T value;
  std::unique_ptr<OSTreeNode> left;
  std::unique_ptr<OSTreeNode> right;
  uint64_t weight;

  explicit OSTreeNode(const T& val, uint64_t w = 0)
      : value(val), left(nullptr), right(nullptr), weight(w) {}
};

template <class T>
class EOSTree : public RSTree<T, OSTreeNode<T>> {
 private:
  using WeightMatrix = std::vector<std::vector<uint64_t>>;

  WeightMatrix AW_;  // AW matrix of weights for subtrees
  WeightMatrix AP_;  // AP matrix of path costs for optimal BST
  WeightMatrix AR_;  // AR matrix storing root indices for optimal subtrees

  void CalculateAW(const std::vector<std::pair<T, uint64_t>>& elements) {
    const std::size_t n = elements.size();
    for (std::size_t i = 0; i < n; ++i) {
      for (std::size_t j = i + 1; j < n; ++j) {
        AW_[i][j] = AW_[i][j - 1] + elements[j].second;
      }
    }
  }

  void CalculateAPAndAR() {
    const std::size_t n = AW_.size();

    for (std::size_t i = 0; i < n - 1; ++i) {
      std::size_t j = i + 1;
      AP_[i][j] = AW_[i][j];
      AR_[i][j] = j;
    }

    for (std::size_t h = 2; h < n; ++h) {
      for (std::size_t i = 0; i < n - h; ++i) {
        std::size_t j = i + h;
        std::size_t m = AR_[i][j - 1];
        uint64_t minCost = AP_[i][m - 1] + AP_[m][j];

        for (std::size_t k = m + 1; k <= AR_[i + 1][j]; ++k) {
          uint64_t cost = AP_[i][k - 1] + AP_[k][j];
          if (cost < minCost) {
            m = k;
            minCost = cost;
          }
        }

        AP_[i][j] = minCost + AW_[i][j];
        AR_[i][j] = m;
      }
    }
  }

  void BuildOptimalTree(const std::vector<std::pair<T, uint64_t>>& elements,
                        std::size_t left, std::size_t right) {
    if (left < right) {
      std::size_t k = AR_[left][right];

      this->Add(elements[k].first);

      auto* node = this->SearchImpl(this->root_.get(), elements[k].first);
      if (node) {
        node->weight = elements[k].second;
      }

      BuildOptimalTree(elements, left, k - 1);
      BuildOptimalTree(elements, k, right);
    }
  }

  void PrintMatrix(const WeightMatrix& matrix) const {
    for (const auto& row : matrix) {
      for (const auto& val : row) {
        std::print("{:4} ", val);
      }
      std::println();
    }
  }

  uint64_t CalculateWeightedPathLength(
      const std::unique_ptr<OSTreeNode<T>>& node, uint64_t level) const {
    if (!node) return 0;
    return node->weight * level +
           CalculateWeightedPathLength(node->left, level + 1) +
           CalculateWeightedPathLength(node->right, level + 1);
  }

  uint64_t CalculateTotalWeight(
      const std::unique_ptr<OSTreeNode<T>>& node) const {
    if (!node) return 0;
    return node->weight + CalculateTotalWeight(node->left) +
           CalculateTotalWeight(node->right);
  }

  std::unordered_map<T, uint64_t> weight_map_;

 public:
  explicit EOSTree(std::vector<std::pair<T, uint64_t>> elements) {
    elements.insert(elements.begin(), {T{}, 0});

    const std::size_t n = elements.size();
    AW_ = WeightMatrix(n, std::vector<uint64_t>(n, 0));
    AP_ = WeightMatrix(n, std::vector<uint64_t>(n, 0));
    AR_ = WeightMatrix(n, std::vector<uint64_t>(n, 0));

    CalculateAW(elements);
    CalculateAPAndAR();
    BuildOptimalTree(elements, 0, n - 1);
  }

  void PrintAW() const {
    std::println("AW matrix:");
    PrintMatrix(AW_);
  }

  void PrintAP() const {
    std::println("AP matrix:");
    PrintMatrix(AP_);
  }

  void PrintAR() const {
    std::println("AR matrix:");
    PrintMatrix(AR_);
  }

  const WeightMatrix& GetAW() const { return AW_; }
  const WeightMatrix& GetAP() const { return AP_; }
  const WeightMatrix& GetAR() const { return AR_; }

  double GetWeightedAverageHeight() const {
    uint64_t totalWeight = CalculateTotalWeight(this->root_);
    if (totalWeight == 0) return 0.0;
    return static_cast<double>(CalculateWeightedPathLength(this->root_, 1)) /
           totalWeight;
  }
};

template <class T>
class OSTreeA1 : public RSTree<T, OSTreeNode<T>> {
 private:
  uint64_t CalculateWeightedPathLength(
      const std::unique_ptr<OSTreeNode<T>>& node, uint64_t level) const {
    if (!node) return 0;
    return node->weight * level +
           CalculateWeightedPathLength(node->left, level + 1) +
           CalculateWeightedPathLength(node->right, level + 1);
  }

  uint64_t CalculateTotalWeight(
      const std::unique_ptr<OSTreeNode<T>>& node) const {
    if (!node) return 0;
    return node->weight + CalculateTotalWeight(node->left) +
           CalculateTotalWeight(node->right);
  }

  std::unordered_map<T, uint64_t> weight_map_;

 public:
  explicit OSTreeA1(std::vector<std::pair<T, uint64_t>> elements) {
    std::sort(elements.begin(), elements.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    for (const auto& elem : elements) {
      this->Add(elem.first);
      auto* node = this->SearchImpl(this->root_.get(), elem.first);
      if (node) {
        node->weight = elem.second;
      }
    }
  }

  double GetWeightedAverageHeight() const {
    uint64_t totalWeight = CalculateTotalWeight(this->root_);
    if (totalWeight == 0) return 0.0;
    return static_cast<double>(CalculateWeightedPathLength(this->root_, 1)) /
           totalWeight;
  }
};

template <class T>
class OSTreeA2 : public RSTree<T, OSTreeNode<T>> {
 private:
  void BuildTree(const std::vector<std::pair<T, uint64_t>>& elements,
                 int64_t left, int64_t right) {
    if (left > right) return;

    uint64_t totalWeight = 0;
    for (int64_t i = left; i <= right; ++i) {
      totalWeight += elements[i].second;
    }

    uint64_t currentWeight = 0;
    int64_t splitIndex = left;

    for (int64_t i = left; i < right; ++i) {
      currentWeight += elements[i].second;
      if (currentWeight * 2 >= totalWeight) {
        splitIndex = i;
        break;
      }
    }

    this->Add(elements[splitIndex].first);
    auto* node =
        this->SearchImpl(this->root_.get(), elements[splitIndex].first);
    if (node) {
      node->weight = elements[splitIndex].second;
    }

    BuildTree(elements, left, splitIndex - 1);
    BuildTree(elements, splitIndex + 1, right);
  }

  uint64_t CalculateWeightedPathLength(
      const std::unique_ptr<OSTreeNode<T>>& node, uint64_t level) const {
    if (!node) return 0;
    return node->weight * level +
           CalculateWeightedPathLength(node->left, level + 1) +
           CalculateWeightedPathLength(node->right, level + 1);
  }

  uint64_t CalculateTotalWeight(
      const std::unique_ptr<OSTreeNode<T>>& node) const {
    if (!node) return 0;
    return node->weight + CalculateTotalWeight(node->left) +
           CalculateTotalWeight(node->right);
  }

  std::unordered_map<T, uint64_t> weight_map_;

 public:
  explicit OSTreeA2(std::vector<std::pair<T, uint64_t>> elements) {
    std::sort(elements.begin(), elements.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });

    BuildTree(elements, 0, elements.size() - 1);
  }

  double GetWeightedAverageHeight() const {
    uint64_t totalWeight = CalculateTotalWeight(this->root_);
    if (totalWeight == 0) return 0.0;
    return static_cast<double>(CalculateWeightedPathLength(this->root_, 1)) /
           totalWeight;
  }
};