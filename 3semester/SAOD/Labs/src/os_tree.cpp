#include "os_tree.hpp"

template <class T>
EOSTree<T>::EOSTree(std::vector<std::pair<T, uint64_t>> elements) {
  elements.insert(elements.begin(), {T{}, 0});

  const std::size_t n = elements.size();
  AW_ = WeightMatrix(n, std::vector<uint64_t>(n, 0));
  AP_ = WeightMatrix(n, std::vector<uint64_t>(n, 0));
  AR_ = WeightMatrix(n, std::vector<uint64_t>(n, 0));

  CalculateAW(elements);
  CalculateAPAndAR();
  BuildOptimalTree(elements, 0, n - 1);
}

template <class T>
void EOSTree<T>::CalculateAW(
    const std::vector<std::pair<T, uint64_t>>& elements) {
  const std::size_t n = elements.size();
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = i + 1; j < n; ++j) {
      AW_[i][j] = AW_[i][j - 1] + elements[j].second;
    }
  }
}

template <class T>
void EOSTree<T>::CalculateAPAndAR() {
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
template <class T>
void EOSTree<T>::PrintAW() const {
  std::println("AW matrix:");
  PrintMatrix(AW_);
}

template <class T>
void EOSTree<T>::PrintAP() const {
  std::println("AP matrix:");
  PrintMatrix(AP_);
}

template <class T>
void EOSTree<T>::PrintAR() const {
  std::println("AR matrix:");
  PrintMatrix(AR_);
}

template <class T>
void EOSTree<T>::BuildOptimalTree(
    const std::vector<std::pair<T, uint64_t>>& elements, std::size_t left,
    std::size_t right) {
  if (left < right) {
    std::size_t k = AR_[left][right];
    this->Add(elements[k].first);
    BuildOptimalTree(elements, left, k - 1);
    BuildOptimalTree(elements, k, right);
  }
}

template <class T>
void EOSTree<T>::PrintMatrix(const WeightMatrix& matrix) const {
  for (const auto& row : matrix) {
    for (const auto& val : row) {
      std::print("{:4} ", val);
    }
    std::println();
  }
}

template <class T>
uint64_t EOSTree<T>::CalculateWeightedPathLength(
    const std::unique_ptr<OSTreeNode<T>>& node, uint64_t level) const {
  if (!node) return 0;
  return node->weight * level +
         CalculateWeightedPathLength(node->left, level + 1) +
         CalculateWeightedPathLength(node->right, level + 1);
}

template <class T>
uint64_t EOSTree<T>::CalculateTotalWeight(
    const std::unique_ptr<OSTreeNode<T>>& node) const {
  if (!node) return 0;
  return node->weight + CalculateTotalWeight(node->left) +
         CalculateTotalWeight(node->right);
}

template <class T>
double EOSTree<T>::GetWeightedAverageHeight() const {
  uint64_t totalWeight = CalculateTotalWeight(this->root_);
  if (totalWeight == 0) return 0.0;
  return static_cast<double>(CalculateWeightedPathLength(this->root_, 1)) /
         totalWeight;
}

template <class T>
OSTreeA1<T>::OSTreeA1(std::vector<std::pair<T, uint64_t>> elements) {
  std::sort(elements.begin(), elements.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });

  for (const auto& elem : elements) {
    this->Add(elem.first);
  }
}

template <class T>
void OSTreeA2<T>::BuildTree(const std::vector<std::pair<T, uint64_t>>& elements,
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
  BuildTree(elements, left, splitIndex - 1);
  BuildTree(elements, splitIndex + 1, right);
}

template <class T>
OSTreeA2<T>::OSTreeA2(std::vector<std::pair<T, uint64_t>> elements) {
  std::sort(elements.begin(), elements.end(),
            [](const auto& a, const auto& b) { return a.first < b.first; });

  BuildTree(elements, 0, elements.size() - 1);
}

template class RSTree<int, OSTreeNode<int>>;
template class RSTree<double, OSTreeNode<double>>;
template class RSTree<float, OSTreeNode<float>>;

template class EOSTree<int>;
template class EOSTree<double>;
template class EOSTree<float>;

template class OSTreeA1<int>;
template class OSTreeA1<double>;
template class OSTreeA1<float>;

template class OSTreeA2<int>;
template class OSTreeA2<double>;
template class OSTreeA2<float>;

template class BaseTree<int, OSTreeNode<int>>;
template class BaseTree<double, OSTreeNode<double>>;
template class BaseTree<float, OSTreeNode<float>>;