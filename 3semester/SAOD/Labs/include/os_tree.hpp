#pragma once

#include <algorithm>
#include <utility>
#include <vector>

#include "rs_tree.hpp"

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

  WeightMatrix AW_;
  WeightMatrix AP_;
  WeightMatrix AR_;

  void CalculateAW(const std::vector<std::pair<T, uint64_t>>& elements);
  void CalculateAPAndAR();
  void BuildOptimalTree(const std::vector<std::pair<T, uint64_t>>& elements,
                        std::size_t left, std::size_t right);
  void PrintMatrix(const WeightMatrix& matrix) const;
  uint64_t CalculateWeightedPathLength(
      const std::unique_ptr<OSTreeNode<T>>& node, uint64_t level) const;
  uint64_t CalculateTotalWeight(
      const std::unique_ptr<OSTreeNode<T>>& node) const;

 public:
  explicit EOSTree(std::vector<std::pair<T, uint64_t>> elements);

  void PrintAW() const;
  void PrintAP() const;
  void PrintAR() const;

  const WeightMatrix& GetAW() const { return AW_; }
  const WeightMatrix& GetAP() const { return AP_; }
  const WeightMatrix& GetAR() const { return AR_; }

  double GetWeightedAverageHeight() const;
};

template <class T>
class OSTreeA1 : public RSTree<T, OSTreeNode<T>> {
 public:
  explicit OSTreeA1(std::vector<std::pair<T, uint64_t>> elements);
};

template <class T>
class OSTreeA2 : public RSTree<T, OSTreeNode<T>> {
 private:
  void BuildTree(const std::vector<std::pair<T, uint64_t>>& elements,
                 int64_t left, int64_t right);

 public:
  explicit OSTreeA2(std::vector<std::pair<T, uint64_t>> elements);
};