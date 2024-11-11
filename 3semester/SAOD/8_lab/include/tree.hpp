#pragma once

#include <algorithm>
#include <print>
#include <utility>
#include <vector>

template <class T>
struct TreeNode {
  T value;
  TreeNode *left, *right;

  explicit TreeNode(const T& val) : value(val), left(nullptr), right(nullptr) {}
};

template <class T>
class ITree {
 public:
  virtual void add(const T&) = 0;
  virtual void remove(const T& value) = 0;
  virtual void clear() = 0;
  virtual void printFromUpToDown() = 0;
  virtual void printFromLeftToRight() = 0;
  virtual void printFromDownToUp() = 0;
  virtual std::size_t getSize() = 0;
  virtual std::size_t getHeight() = 0;
  virtual double getMediumHeight() = 0;
  virtual T getSum() = 0;
};

// The binary tree virtual class
template <class T, class TNode = TreeNode<T>>
class BaseTree : public ITree<T> {
 protected:
  TNode* root;

  static void removeBranch(TNode* p) {
    if (p != nullptr) {
      removeBranch(p->left);
      removeBranch(p->right);
      delete p;
    }
  }

  static void printFromUpToDown(TNode* p) {
    if (p != nullptr) {
      std::print("{} ", p->value);
      printFromUpToDown(p->left);
      printFromUpToDown(p->right);
    }
  }

  static void printFromLeftToRight(TNode* p) {
    if (p != nullptr) {
      printFromLeftToRight(p->left);
      std::print("{} ", p->value);
      printFromLeftToRight(p->right);
    }
  }

  static void printFromDownToUp(TNode* p) {
    if (p != nullptr) {
      printFromDownToUp(p->left);
      printFromDownToUp(p->right);
      std::print("{} ", p->value);
    }
  }

  static std::size_t getSize(TNode* p) {
    if (p == nullptr) return 0;
    return 1 + getSize(p->left) + getSize(p->right);
  }

  static std::size_t getHeight(TNode* p) {
    if (p == nullptr) return 0;
    return std::max(getHeight(p->left), getHeight(p->right)) + 1;
  }

  static std::size_t getSumLenght(TNode* p, std::size_t l) {
    if (p == nullptr) return 0;
    return l + getSumLenght(p->left, l + 1) + getSumLenght(p->right, l + 1);
  }

  static T getSum(TNode* p) {
    if (p == nullptr) return 0;
    return p->value + getSum(p->left) + getSum(p->right);
  }

  static void getArrayElementsFromLeftToRight(TNode* p,
                                              const std::vector<T>& arr) {
    if (p != nullptr) {
      getArrayElementsFromLeftToRight(p->left, arr);
      arr.push_back(p->value);
      getArrayElementsFromLeftToRight(p->right, arr);
    }
  }

  static void getArrayElementsFromUpToDown(TNode* p,
                                           const std::vector<T>& arr) {
    if (p != nullptr) {
      arr.push_back(p->value);
      getArrayElementsFromUpToDown(p->left, arr);
      getArrayElementsFromUpToDown(p->right, arr);
    }
  }

 public:
  BaseTree() : root(nullptr) {}

  BaseTree(const BaseTree<T>& other) : BaseTree() {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(other.root, arr);
    for (T& elem : arr) this->add(elem);
  }

  ~BaseTree() { clear(); }

  void clear() override {
    removeBranch(root);
    root = nullptr;
  }

  void printFromUpToDown() override {
    printFromUpToDown(root);
    std::println();
  }

  void printFromLeftToRight() override {
    printFromLeftToRight(root);
    std::println();
  }

  void printFromDownToUp() override {
    printFromDownToUp(root);
    std::println();
  }

  std::size_t getSize() override { return getSize(root); }

  std::size_t getHeight() override { return getHeight(root); }

  double getMediumHeight() override {
    return static_cast<double>(getSumLenght(root, 1)) /
           static_cast<double>(getSize(root));
  }

  T getSum() override { return getSum(root); }

  T get(std::size_t index) {
    std::vector<T> arr(getSize());
    getArrayElementsFromLeftToRight(root, arr);
    return arr[index];
  }

  std::vector<T> getArrayElementsFromLeftToRight() {
    std::vector<T> arr;
    getArrayElementsFromLeftToRight(root, arr);
    return arr;
  }

  std::vector<T> getArrayElementsFromUpToDown() {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(root, arr);
    return arr;
  }
};

// The random search tree
template <class T, class TNode = TreeNode<T>>
class RSTree : public BaseTree<T, TNode> {
 protected:
  TNode* addRecurs(const T& val, TNode* cur) {
    if (cur == nullptr) return new TNode(val);

    if (val < cur->value)
      cur->left = addRecurs(val, cur->left);
    else
      cur->right = addRecurs(val, cur->right);
    return cur;
  }

  void removeRight(TNode* cur, const T& value) {
    TNode *min_right = cur->right, *min_right_prev = cur;
    while (min_right->left != nullptr) {
      min_right_prev = min_right;
      min_right = min_right->left;
    }
    cur->value = std::move(min_right->value);
    remove(min_right, min_right_prev, cur->value);
  }

  void removeLeft(TNode* cur, const T& value) {
    TNode *max_left = cur->left, *max_left_prev = cur;
    while (max_left->right != nullptr) {
      max_left_prev = max_left;
      max_left = max_left->right;
    }
    cur->value = std::move(max_left->value);
    remove(max_left, max_left_prev, cur->value);
  }

  void remove(TNode* cur, TNode* prev, const T& value) {
    if (cur == nullptr) return;
    if (this->getSize() == 1) {
      delete this->root;
      this->root = nullptr;
      return;
    }

    if (cur->value == value) {
      if (prev == nullptr) {
        if (cur->left == nullptr && cur->right == nullptr) {
          delete cur;
          this->root = nullptr;
        } else if (cur->right != nullptr)
          removeRight(cur, value);
        else
          removeLeft(cur, value);
      } else {
        if (cur->left == nullptr && cur->right == nullptr) {
          if (cur->value < prev->value) {
            delete cur;
            prev->left = nullptr;
          } else {
            delete cur;
            prev->right = nullptr;
          }
        } else if (cur->right != nullptr)
          removeRight(cur, value);
        else
          removeLeft(cur, value);
      }
    } else {
      if (value < cur->value)
        remove(cur->left, cur, value);
      else
        remove(cur->right, cur, value);
    }
  }

 public:
  void add(const T& val) override {
    if (this->root == nullptr)
      this->root = new TNode(val);
    else {
      TNode *cur = this->root, *pred = nullptr;

      do {
        pred = cur;
        if (val < cur->value)
          cur = cur->left;
        else
          cur = cur->right;
      } while (cur != nullptr);

      if (val < pred->value)
        pred->left = new TNode(val);
      else
        pred->right = new TNode(val);
    }
  }

  void addRecurs(const T& val) { this->root = addRecurs(val, this->root); }

  void remove(const T& value) override { remove(this->root, nullptr, value); }
};

// The perfectly balanced search tree
template <class T, class TNode = TreeNode<T>>
class PBSTree : public BaseTree<T, TNode> {
  TNode* newTree(int64_t left, int64_t right, const std::vector<T>& arr) {
    if (left > right) return nullptr;
    std::size_t medium = (left + right) / 2;
    TNode* p = new TNode(arr[medium]);
    p->left = newTree(left, medium - 1, arr);
    p->right = newTree(medium + 1, right, arr);
    return p;
  }

 public:
  PBSTree() = default;

  explicit PBSTree(std::vector<T> arr) {
    std::sort(arr.begin(), arr.end());
    this->root = newTree(0, arr.size() - 1, arr);
  }

  void add(const T& val) override {
    std::vector<T> arr;
    this->getArrayElementsFromLeftToRight(this->root, arr);
    arr.push_back(val);
    std::sort(arr.begin(), arr.end());
    this->clear();
    this->root = newTree(0, arr.size() - 1, arr);
  }

  void remove(const T& value) override {}
};

template <class T, std::size_t M = 3>
class BTree : public ITree<T> {
 protected:
  struct Node {
    std::vector<T> values;
    std::vector<Node*> child_nodes;

    Node() : values(), child_nodes(1, nullptr) {
      values.reserve(M);
      child_nodes.reserve(M + 1);
    }

    explicit Node(const T& val) : values(1, val), child_nodes(2, nullptr) {}

    std::size_t add(const T& val) {
      std::size_t I = 0;
      auto i = values.begin();
      auto j = child_nodes.begin();
      while (i != values.end() && val > *i) {
        I++;
        i++;
        j++;
      }
      values.insert(i, val);
      child_nodes.insert(j, nullptr);
      return I;
    }

    std::size_t add(const T& val, Node* p) {
      std::size_t I = add(val);
      child_nodes.at(I) = p;
      return I;
    }
  };

  Node* root;
  std::size_t size;

  Node* newRoot() {
    Node *new_root = new Node, *left = new Node, *right = new Node;

    std::size_t center = M / 2;

    for (std::size_t i = 0; i < center; i++)
      left->add(root->values.at(i), root->child_nodes.at(i));
    left->child_nodes.back() = root->child_nodes.at(center);

    for (std::size_t i = center + 1; i < M; i++)
      right->add(root->values.at(i), root->child_nodes.at(i));
    right->child_nodes.back() = root->child_nodes.back();

    new_root->add(root->values.at(center));
    new_root->child_nodes.front() = left;
    new_root->child_nodes.back() = right;

    delete root;
    root = new_root;

    return root;
  }

  void balanced(Node** cur, Node** prev) {
    Node *left = new Node, *right = new Node;

    std::size_t center = M / 2;

    for (std::size_t i = 0; i < center; i++)
      left->add((*cur)->values.at(i), (*cur)->child_nodes.at(i));
    left->child_nodes.back() = (*cur)->child_nodes.at(center);

    for (std::size_t i = center + 1; i < M; i++)
      right->add((*cur)->values.at(i), (*cur)->child_nodes.at(i));
    right->child_nodes.back() = (*cur)->child_nodes.back();

    std::size_t elem_position = (*prev)->add((*cur)->values.at(center));
    delete *cur;
    (*prev)->child_nodes.at(elem_position) = left;
    (*prev)->child_nodes.at(elem_position + 1) = right;
  }

  void add(const T& val, Node** cur, Node** prev) {
    for (std::size_t i = 0; i < (*cur)->values.size(); i++) {
      if (val < (*cur)->values.at(i)) {
        if ((*cur)->child_nodes.at(i) == nullptr)
          (*cur)->add(val);
        else
          add(val, &(*cur)->child_nodes.at(i), cur);
        break;
      } else if (i + 1 == (*cur)->values.size()) {
        if ((*cur)->child_nodes.at(i + 1) == nullptr)
          (*cur)->add(val);
        else
          add(val, &(*cur)->child_nodes.at(i + 1), cur);
        break;
      }
    }

    if ((*cur)->values.size() == M) {
      if (prev == nullptr)
        (*cur) = newRoot();
      else
        balanced(cur, prev);
    }
  }

  static void printFromUpToDown(Node* p) {
    if (p != nullptr) {
      for (const T& val : p->values) std::print("{} ", val);
      for (Node* next : p->child_nodes) printFromUpToDown(next);
    }
  }

  static void printFromLeftToRight(Node* p) {
    if (p != nullptr) {
      for (std::size_t i = 0; i < p->values.size(); i++) {
        printFromLeftToRight(p->child_nodes.at(i));
        std::print("{} ", p->values.at(i));
      }
      printFromLeftToRight(p->child_nodes.back());
    }
  }

  static void printFromDownToUp(Node* p) {
    if (p != nullptr) {
      for (Node* next : p->child_nodes) printFromUpToDown(next);
      for (const T& val : p->values) std::print("{} ", val);
    }
  }

  void clear(Node* p) {
    if (p == nullptr) return;
    for (Node*& c : p->child_nodes) clear(c);
    delete p;
  }

  std::size_t getSumLenght(Node* p, std::size_t l) {
    if (p == nullptr) return 0;
    std::size_t sum = p->values.size();
    for (Node* cp : p->child_nodes) sum += getSumLenght(cp, l + 1);
    return l + sum;
  }

  std::size_t getSum(Node* p) {
    if (p == nullptr) return 0;
    T sum{}, sum_child{};
    for (const T& val : p->values) sum += val;
    for (Node* cp : p->child_nodes) sum_child += getSum(cp);
    return sum + sum_child;
  }

  std::size_t getLevelsCount(Node* p) {
    if (p == nullptr) return 0;
    std::size_t sum = 0;
    for (Node* cp : p->child_nodes) sum += getLevelsCount(cp);
    return sum + 1;
  }

 public:
  BTree() : root(nullptr), size(0) {
    if (M < 3) throw std::logic_error("Suka, ti che eblan?");
  }

  ~BTree() { clear(); }

  void add(const T& val) {
    if (root == nullptr)
      root = new Node(val);
    else
      add(val, &root, nullptr);
    size++;
  }

  void printFromUpToDown() {
    printFromUpToDown(root);
    std::println();
  }

  void printFromLeftToRight() {
    printFromLeftToRight(root);
    std::println();
  }

  void printFromDownToUp() {
    printFromDownToUp(root);
    std::println();
  }

  void remove(const T& value) override {}

  void clear() override {
    clear(root);
    root = nullptr;
  }

  std::size_t getSize() override { return size; }

  std::size_t getHeight() override {
    std::size_t height = 1;
    Node* p = root;
    while (p->child_nodes.front() != nullptr) {
      p = p->child_nodes.front();
      height++;
    }
    return height;
  }

  double getMediumHeight() override {
    return static_cast<double>(getSumLenght(root, 1)) /
           static_cast<double>(getSize());
  }

  T getSum() override { return getSum(root); }

  std::size_t getLevelsCount() { return getLevelsCount(root); }
};

template <class T>
struct AVLTreeNode {
  T value;
  AVLTreeNode *left, *right;
  int64_t balance;

  explicit AVLTreeNode(const T& val)
      : value(val), left(nullptr), right(nullptr), balance(0) {}
};

// The AVL tree
template <class T>
class AVLTree : public BaseTree<T, AVLTreeNode<T>> {
 protected:
  AVLTreeNode<T>* LLTurn(AVLTreeNode<T>* p) {
    AVLTreeNode<T>* q = p->left;
    p->balance = 0;
    q->balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
    return p;
  }

  AVLTreeNode<T>* RRTurn(AVLTreeNode<T>* p) {
    AVLTreeNode<T>* q = p->right;
    p->balance = 0;
    q->balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
    return p;
  }

  AVLTreeNode<T>* LRTurn(AVLTreeNode<T>* p) {
    AVLTreeNode<T>* q = p->left;
    AVLTreeNode<T>* r = q->right;

    if (r->balance < 0)
      p->balance = 1;
    else
      p->balance = 0;

    if (r->balance > 0)
      q->balance = -1;
    else
      q->balance = 0;

    r->balance = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
    return p;
  }

  AVLTreeNode<T>* RLTurn(AVLTreeNode<T>* p) {
    AVLTreeNode<T>* q = p->right;
    AVLTreeNode<T>* r = q->left;

    if (r->balance > 0)
      p->balance = -1;
    else
      p->balance = 0;

    if (r->balance < 0)
      q->balance = 1;
    else
      q->balance = 0;

    r->balance = 0;
    q->left = r->right;
    p->right = r->left;
    r->right = q;
    r->left = p;
    p = r;
    return p;
  }

  AVLTreeNode<T>* add(const T& val, AVLTreeNode<T>* p, bool& rost) {
    if (p == nullptr) {
      p = new AVLTreeNode(val);
      rost = true;
    } else if (p->value > val) {
      p->left = add(val, p->left, rost);
      if (rost) {
        if (p->balance > 0) {
          p->balance = 0;
          rost = false;
        } else if (p->balance == 0) {
          p->balance = -1;
          rost = true;
        } else {
          if (p->left->balance < 0)
            p = LLTurn(p);
          else
            p = LRTurn(p);
          rost = false;
        }
      }
    } else {
      p->right = add(val, p->right, rost);
      if (rost) {
        if (p->balance < 0) {
          p->balance = 0;
          rost = false;
        } else if (p->balance == 0) {
          p->balance = 1;
          rost = true;
        } else {
          if (p->right->balance > 0)
            p = RRTurn(p);
          else
            p = RLTurn(p);
          rost = false;
        }
      }
    }
    return p;
  }

  AVLTreeNode<T>* RR1Turn(AVLTreeNode<T>* p, bool& umen) {
    AVLTreeNode<T>* q = p->right;
    if (q->balance == 0) {
      q->balance = -1;
      p->balance = 1;
      umen = false;
    } else {
      q->balance = 0;
      p->balance = 0;
    }
    p->right = q->left;
    q->left = p;
    p = q;
    return p;
  }

  AVLTreeNode<T>* LL1Turn(AVLTreeNode<T>* p, bool& umen) {
    AVLTreeNode<T>* q = p->left;
    if (q->balance == 0) {
      q->balance = 1;
      p->balance = -1;
      umen = false;
    } else {
      q->balance = 0;
      p->balance = 0;
    }
    p->left = q->right;
    q->right = p;
    p = q;
    return p;
  }

  AVLTreeNode<T>* BL(AVLTreeNode<T>* p, bool& umen) {
    if (p->balance == -1)
      p->balance = 0;
    else if (p->balance == 0) {
      p->balance = 1;
      umen = false;
    } else if (p->balance == 1) {
      if (p->right->balance >= 0)
        p = RR1Turn(p, umen);
      else
        p = RLTurn(p);
    }
    return p;
  }

  AVLTreeNode<T>* BR(AVLTreeNode<T>* p, bool& umen) {
    if (p->balance == 1)
      p->balance = 0;
    else if (p->balance == 0) {
      p->balance = -1;
      umen = false;
    } else if (p->balance == -1) {
      if (p->left->balance <= 0)
        p = LL1Turn(p, umen);
      else
        p = LRTurn(p);
    }
    return p;
  }

  void del(AVLTreeNode<T>** p, AVLTreeNode<T>** q, bool& umen) {
    if ((*p)->right != nullptr) {
      del(&(*p)->right, q, umen);
      if (umen) *p = BR(*p, umen);
    } else {
      (*q)->value = (*p)->value;
      *q = *p;
      *p = (*p)->left;
      umen = true;
    }
  }

  AVLTreeNode<T>* remove(const T& val, AVLTreeNode<T>* p, bool& umen) {
    if (p == nullptr) {
    } else if (val < p->value) {
      p->left = remove(val, p->left, umen);
      if (umen) p = BL(p, umen);
    } else if (val > p->value) {
      p->right = remove(val, p->right, umen);
      if (umen) p = BR(p, umen);
    } else {
      AVLTreeNode<T>* q = p;
      if (q->left == nullptr) {
        p = q->right;
        umen = true;
      } else if (q->right == nullptr) {
        p = q->left;
        umen = true;
      } else {
        del(&q->left, &q, umen);
        if (umen) p = BL(p, umen);
      }
      delete q;
    }
    return p;
  }

 public:
  void add(const T& val) override {
    bool rost = false;
    this->root = add(val, this->root, rost);
  }

  void remove(const T& val) override {
    bool umen = false;
    this->root = remove(val, this->root, umen);
  }
};

namespace os_tree {
template <class T>
struct OSTree {
  T value;
  OSTree *left, *right;
  uint64_t weight;

  explicit OSTree(const T& val)
      : value(val), left(nullptr), right(nullptr), weight(0) {}

  OSTree(const T& val, const uint64_t& w)
      : value(val), left(nullptr), right(nullptr), weight(w) {}
};

// The exact optimal search tree
template <class T>
class EOSTree : public RSTree<T, OSTree<T>> {
  using WeightsMatrix_t = std::vector<std::vector<uint64_t>>;

 protected:
  WeightsMatrix_t AW;
  WeightsMatrix_t AP;
  WeightsMatrix_t AR;

  void calculateAW(const std::vector<std::pair<T, uint64_t>>& arr) {
    for (std::size_t i = 0; i < AW.size(); i++)
      for (std::size_t j = i + 1; j < AW.size(); j++)
        AW.at(i).at(j) = AW.at(i).at(j - 1) + arr.at(j).second;
  }

  void calculateAPAndAR() {
    for (int i = 0; i < AW.size() - 1; i++) {
      int j = i + 1;
      AP.at(i).at(j) = AW.at(i).at(j);
      AR.at(i).at(j) = j;
    }
    for (int h = 2; h < AW.size(); h++) {
      for (int i = 0; i < AW.size() - h; i++) {
        int j = i + h;
        int m = AR.at(i).at(j - 1);
        int min = AP.at(i).at(m - 1) + AP.at(m).at(j);
        for (int k = m + 1; k <= AR.at(i + 1).at(j); k++) {
          int x = AP.at(i).at(k - 1) + AP.at(k).at(j);
          if (x < min) {
            m = k;
            min = x;
          }
        }
        AP.at(i).at(j) = min + AW.at(i).at(j);
        AR.at(i).at(j) = m;
      }
    }
  }

  void create(const std::vector<std::pair<T, uint64_t>>& arr, std::size_t left,
              std::size_t right) {
    if (left < right) {
      std::size_t k = AR.at(left).at(right);
      add(arr.at(k));
      create(arr, left, k - 1);
      create(arr, k, right);
    }
  }

  void printA(const WeightsMatrix_t& A) {
    for (const auto& vec : A) {
      for (const auto& weight : vec) std::print("{} ", weight);
      std::println();
    }
  }

  int sumLengthWaysTreeDOP(OSTree<T>* p, int L) {
    if (p == nullptr) return 0;
    return p->weight * L + sumLengthWaysTreeDOP(p->left, L + 1) +
           sumLengthWaysTreeDOP(p->right, L + 1);
  }

  int weightTree(OSTree<T>* p) {
    if (p == nullptr) return 0;
    return p->weight + weightTree(p->left) + weightTree(p->right);
  }

  void add(const std::pair<T, uint64_t>& val) {
    if (this->root == nullptr)
      this->root = new OSTree(val.first, val.second);
    else {
      OSTree<T>*cur = this->root, *pred = nullptr;

      do {
        pred = cur;
        if (val.first < cur->value)
          cur = cur->left;
        else
          cur = cur->right;
      } while (cur != nullptr);

      if (val.first < pred->value)
        pred->left = new OSTree(val.first, val.second);
      else
        pred->right = new OSTree(val.first, val.second);
    }
  }

 public:
  explicit EOSTree(std::vector<std::pair<T, uint64_t>> arr)
      : AW(arr.size() + 1, std::vector<uint64_t>(arr.size() + 1, 0)),
        AP(arr.size() + 1, std::vector<uint64_t>(arr.size() + 1, 0)),
        AR(arr.size() + 1, std::vector<uint64_t>(arr.size() + 1, 0)) {
    arr.push_back(std::pair<T, uint64_t>());
    calculateAW(arr);
    calculateAPAndAR();
    create(arr, 0, arr.size() - 1);
  }

  void printAW() { printA(AW); }

  void printAP() { printA(AP); }

  void printAR() { printA(AR); }

  const WeightsMatrix_t& getAW() { return AW; }

  const WeightsMatrix_t& getAP() { return AP; }

  const WeightsMatrix_t& getAR() { return AR; }

  double weightedAverageHeightTree() {
    return static_cast<double>(sumLengthWaysTreeDOP(this->root, 1)) /
           static_cast<double>(weightTree(this->root));
  }
};

template <class T>
class OSTreeA1 : public RSTree<T, OSTree<T>> {
 public:
  explicit OSTreeA1(std::vector<std::pair<T, uint64_t>> arr) {
    std::sort(
        arr.begin(), arr.end(),
        [](const std::pair<T, uint64_t>& a, const std::pair<T, uint64_t>& b) {
          return a.second < b.second;
        });
    for (const std::pair<T, uint64_t>& elem : arr) this->add(elem.first);
  }
};

template <class T>
class OSTreeA2 : public RSTree<T, OSTree<T>> {
 protected:
  void create(const std::vector<std::pair<T, uint64_t>>& arr, int64_t left,
              int64_t right) {
    std::size_t wes = 0, sum = 0;
    if (left <= right) {
      std::size_t i = left;
      for (i = left; i < right; i++) wes += arr.at(i).second;
      for (i = left; i < right; i++) {
        if (sum < wes / 2 && sum + arr.at(i).second > wes / 2) break;
        sum += arr.at(i).second;
      }
      add(arr.at(i));
      create(arr, left, i - 1);
      create(arr, i + 1, right);
    }
  }

  void add(const std::pair<T, uint64_t>& val) {
    if (this->root == nullptr)
      this->root = new OSTree(val.first, val.second);
    else {
      OSTree<T>*cur = this->root, *pred = nullptr;

      do {
        pred = cur;
        if (val.first < cur->value)
          cur = cur->left;
        else
          cur = cur->right;
      } while (cur != nullptr);

      if (val.first < pred->value)
        pred->left = new OSTree(val.first, val.second);
      else
        pred->right = new OSTree(val.first, val.second);
    }
  }

 public:
  OSTreeA2(const std::vector<std::pair<T, uint64_t>>& arr) {
    create(arr, 0, arr.size() - 1);
  }
};
}  // namespace os_tree
