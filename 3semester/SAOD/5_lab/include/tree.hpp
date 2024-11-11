#pragma once

#include <algorithm>
#include <print>
#include <vector>

/**
 * @brief A structure representing a node in a binary tree.
 *
 * @tparam T The type of the value stored in the node.
 */
template <class T>
struct TreeNode {
  T value;         /**< The value stored in the node. */
  TreeNode* left;  /**< Pointer to the left child node. */
  TreeNode* right; /**< Pointer to the right child node. */
  int64_t balance; /**< Balance factor used for AVL trees. */

  /**
   * @brief Constructor to create a tree node with a given value.
   *
   * @param val The value to store in the node.
   */
  TreeNode(const T& val)
      : value(val), left(nullptr), right(nullptr), balance(0) {}
};

/**
 * @brief A base interface class for binary trees, supporting common tree
 * operations.
 *
 * @tparam T The type of value stored in the tree.
 */
template <class T>
class ITree {
 protected:
  TreeNode<T>* root; /**< Root node of the tree. */
  /**
   * @brief Recursively removes a branch of the tree.
   *
   * @param p Pointer to the node to be removed.
   */
  static void removeBranch(TreeNode<T>* p) {
    if (p != nullptr) {
      removeBranch(p->left);
      removeBranch(p->right);
      delete p;
    }
  }
  /**
   * @brief Prints the tree values in "up to down" order (pre-order traversal).
   *
   * @param p Pointer to the node to start printing from.
   */
  static void printFromUpToDown(TreeNode<T>* p) {
    if (p != nullptr) {
      std::print("{} ", p->value);
      printFromUpToDown(p->left);
      printFromUpToDown(p->right);
    }
  }
  /**
   * @brief Prints the tree values in "left to right" order (in-order
   * traversal).
   *
   * @param p Pointer to the node to start printing from.
   */
  static void printFromLeftToRight(TreeNode<T>* p) {
    if (p != nullptr) {
      printFromLeftToRight(p->left);
      std::print("{} ", p->value);
      printFromLeftToRight(p->right);
    }
  }
  /**
   * @brief Prints the tree values in "down to up" order (post-order traversal).
   *
   * @param p Pointer to the node to start printing from.
   */
  static void printFromDownToUp(TreeNode<T>* p) {
    if (p != nullptr) {
      printFromDownToUp(p->left);
      printFromDownToUp(p->right);
      std::print("{} ", p->value);
    }
  }
  /**
   * @brief Recursively gets the size of the tree.
   *
   * @param p Pointer to the node to start counting from.
   * @return The size of the tree.
   */
  static std::size_t getSize(TreeNode<T>* p) {
    if (p == nullptr) return 0;
    return 1 + getSize(p->left) + getSize(p->right);
  }
  /**
   * @brief Recursively calculates the height of the tree.
   *
   * @param p Pointer to the node to calculate the height from.
   * @return The height of the tree.
   */
  static std::size_t getHeight(TreeNode<T>* p) {
    if (p == nullptr) return 0;
    return std::max(getHeight(p->left), getHeight(p->right)) + 1;
  }
  /**
   * @brief Recursively calculates the sum of the lengths of paths to each node.
   *
   * @param p Pointer to the node to calculate from.
   * @param l The current path length.
   * @return The sum of all path lengths.
   */
  static std::size_t getSumLenght(TreeNode<T>* p, std::size_t l) {
    if (p == nullptr) return 0;
    return l + getSumLenght(p->left, l + 1) + getSumLenght(p->right, l + 1);
  }
  /**
   * @brief Recursively sums all the values in the tree.
   *
   * @param p Pointer to the node to start summing from.
   * @return The sum of all node values.
   */
  static T getSum(TreeNode<T>* p) {
    if (p == nullptr) return 0;
    return p->value + getSum(p->left) + getSum(p->right);
  }
  /**
   * @brief Recursively adds all node values to an array in "left to right"
   * order (in-order).
   *
   * @param p Pointer to the node to start adding from.
   * @param arr Reference to the array to add values to.
   */
  static void getArrayElementsFromLeftToRight(TreeNode<T>* p,
                                              std::vector<T>& arr) {
    if (p != nullptr) {
      getArrayElementsFromLeftToRight(p->left, arr);
      arr.push_back(p->value);
      getArrayElementsFromLeftToRight(p->right, arr);
    }
  }
  /**
   * @brief Recursively adds all node values to an array in "up to down" order
   * (pre-order).
   *
   * @param p Pointer to the node to start adding from.
   * @param arr Reference to the array to add values to.
   */
  static void getArrayElementsFromUpToDown(TreeNode<T>* p,
                                           std::vector<T>& arr) {
    if (p != nullptr) {
      arr.push_back(p->value);
      getArrayElementsFromUpToDown(p->left, arr);
      getArrayElementsFromUpToDown(p->right, arr);
    }
  }

 public:
  /**
   * @brief Default constructor for the tree.
   */
  ITree() : root(nullptr) {}
  /**
   * @brief Copy constructor. Copies elements from another tree.
   *
   * @param other Reference to another tree to copy elements from.
   */
  ITree(const ITree<T>& other) : ITree() {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(other.root, arr);
    for (T& elem : arr) add(elem);
  }
  /**
   * @brief Destructor. Clears the tree and deallocates memory.
   */
  ~ITree() { clear(); }
  /**
   * @brief Clears the tree, deleting all nodes.
   */
  void clear() {
    removeBranch(root);
    root = nullptr;
  }
  /**
   * @brief Prints the tree values in "up to down" order (pre-order traversal).
   */
  void printFromUpToDown() {
    printFromUpToDown(root);
    std::println();
  }
  /**
   * @brief Prints the tree values in "left to right" order (in-order
   * traversal).
   */
  void printFromLeftToRight() {
    printFromLeftToRight(root);
    std::println();
  }
  /**
   * @brief Prints the tree values in "down to up" order (post-order traversal).
   */
  void printFromDownToUp() {
    printFromDownToUp(root);
    std::println();
  }
  /**
   * @brief Returns the size of the tree.
   *
   * @return The number of nodes in the tree.
   */
  std::size_t getSize() { return getSize(root); }
  /**
   * @brief Returns the height of the tree.
   *
   * @return The height of the tree.
   */
  std::size_t getHeight() { return getHeight(root); }
  /**
   * @brief Calculates and returns the average path length to each node.
   *
   * @return The average height of nodes.
   */
  double getMediumHeight() {
    return static_cast<double>(getSumLenght(root, 1)) /
           static_cast<double>(getSize(root));
  }
  /**
   * @brief Calculates and returns the sum of all node values.
   *
   * @return The sum of all node values.
   */
  T getSum() { return getSum(root); }
  /**
   * @brief Retrieves the value at the given index (in in-order traversal).
   *
   * @param index The index of the element to retrieve.
   * @return The value at the specified index.
   */
  T get(std::size_t index) {
    std::vector<T> arr(getSize());
    getArrayElementsFromLeftToRight(root, arr);
    return arr[index];
  }
  /**
   * @brief Retrieves all values from the tree in "left to right" order
   * (in-order).
   *
   * @return A vector containing all tree values.
   */
  std::vector<T> getArrayElementsFromLeftToRight() {
    std::vector<T> arr;
    getArrayElementsFromLeftToRight(root, arr);
    return arr;
  }
  /**
   * @brief Retrieves all values from the tree in "up to down" order (in-order).
   *
   * @return A vector containing all tree values.
   */
  std::vector<T> getArrayElementsFromUpToDown() {
    std::vector<T> arr;
    getArrayElementsFromUpToDown(root, arr);
    return arr;
  }
  /**
   * @brief Adds an element to the tree.
   *
   * @param value The value to add to the tree.
   */
  virtual void add(const T&) = 0;
  virtual void remove(const T& value) = 0;
};

// The binary search tree or the random search tree
/**
 * @brief Randomized search tree class derived from ITree.
 *
 * Provides methods for adding and removing elements in a
 * binary search tree structure.
 *
 * @tparam T The type of elements stored in the tree.
 */
template <class T>
class RSTree : public ITree<T> {
  /**
   * @brief Recursively adds a value to the tree.
   *
   * @param val The value to add.
   * @param cur The current node during recursion.
   * @return The updated node.
   */
  TreeNode<T>* addRecurs(const T& val, TreeNode<T>* cur) {
    if (cur == nullptr) return new TreeNode<T>(val);

    if (val < cur->value)
      cur->left = addRecurs(val, cur->left);
    else
      cur->right = addRecurs(val, cur->right);
    return cur;
  }

  /**
   * @brief Removes the right subtree's minimum node.
   *
   * @param cur The current node being modified.
   * @param value The value of the node being removed.
   */
  void removeRight(TreeNode<T>* cur, const T& value) {
    TreeNode<T>*min_right = cur->right, *min_right_prev = cur;
    while (min_right->left != nullptr) {
      min_right_prev = min_right;
      min_right = min_right->left;
    }
    cur->value = std::move(min_right->value);
    remove(min_right, min_right_prev, cur->value);
  }

  /**
   * @brief Removes the left subtree's maximum node.
   *
   * @param cur The current node being modified.
   * @param value The value of the node being removed.
   */
  void removeLeft(TreeNode<T>* cur, const T& value) {
    TreeNode<T>*max_left = cur->left, *max_left_prev = cur;
    while (max_left->right != nullptr) {
      max_left_prev = max_left;
      max_left = max_left->right;
    }
    cur->value = std::move(max_left->value);
    remove(max_left, max_left_prev, cur->value);
  }

  /**
   * @brief Removes a node from the tree.
   *
   * @param cur The current node being examined.
   * @param prev The parent node of the current node.
   * @param value The value of the node being removed.
   */
  void remove(TreeNode<T>* cur, TreeNode<T>* prev, const T& value) {
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
  /**
   * @brief Adds a value to the tree.
   *
   * @param val The value to add.
   */
  void add(const T& val) override {
    if (this->root == nullptr)
      this->root = new TreeNode(val);
    else {
      TreeNode<T>*cur = this->root, *pred = nullptr;

      do {
        pred = cur;
        if (val < cur->value)
          cur = cur->left;
        else
          cur = cur->right;
      } while (cur != nullptr);

      if (val < pred->value)
        pred->left = new TreeNode(val);
      else
        pred->right = new TreeNode(val);
    }
  }

  /**
   * @brief Adds a value to the tree recursively.
   *
   * @param val The value to add.
   */
  void addRecurs(const T& val) { this->root = addRecurs(val, this->root); }

  /**
   * @brief Removes a value from the tree.
   *
   * @param value The value to remove.
   */
  void remove(const T& value) override { remove(this->root, nullptr, value); }
};

// The perfectly balanced search tree
/**
 * @brief Perfectly balanced search tree class derived from ITree.
 *
 * @tparam T The type of elements stored in the tree.
 */
template <class T>
class PBSTree : public ITree<T> {
  /**
   * @brief Recursively constructs a new balanced tree from sorted elements.
   *
   * @param left The leftmost index in the array.
   * @param right The rightmost index in the array.
   * @param arr The sorted array of values.
   * @return A pointer to the root of the new subtree.
   */
  TreeNode<T>* newTree(int64_t left, int64_t right, const std::vector<T>& arr) {
    if (left > right) return nullptr;
    std::size_t medium = (left + right) / 2;
    TreeNode<T>* p = new TreeNode<T>(arr[medium]);
    p->left = newTree(left, medium - 1, arr);
    p->right = newTree(medium + 1, right, arr);
    return p;
  }

 public:
  /**
   * @brief Default constructor for PBSTree.
   */
  PBSTree() = default;

  /**
   * @brief Constructs a balanced tree from a sorted array of values.
   *
   * @param arr A vector of values to create the tree from.
   */
  PBSTree(std::vector<T> arr) {
    std::sort(arr.begin(), arr.end());
    this->root = newTree(0, arr.size() - 1, arr);
  }

  /**
   * @brief Adds a value to the tree and rebalances.
   *
   * @param val The value to add.
   */
  void add(const T& val) override {
    std::vector<T> arr;
    this->getArrayElementsFromLeftToRight(this->root, arr);
    arr.push_back(val);
    std::sort(arr.begin(), arr.end());
    this->clear();
    this->root = newTree(0, arr.size() - 1, arr);
  }
};

// The AVL tree
/**
 * @brief AVL tree class implementing an auto-balancing binary search tree.
 *
 * The AVL tree maintains balance by ensuring that the heights of the two child
 * subtrees of any node differ by at most one. If at any time they differ by
 * more than one, rebalancing operations (rotations) are performed.
 *
 * @tparam T The type of elements stored in the tree.
 */
template <class T>
class AVLTree : public ITree<T> {
  /**
   * @brief Performs a left-left (LL) rotation.
   *
   * This rotation is used to rebalance the tree when the left child of the left
   * subtree is too deep, resulting in an imbalance.
   *
   * @param p Pointer to the root of the unbalanced subtree.
   * @return A pointer to the new root of the subtree after rotation.
   */
  TreeNode<T>* LLTurn(TreeNode<T>* p) {
    TreeNode<T>* q = p->left;
    p->balance = 0;
    q->balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
    return p;
  }

  /**
   * @brief Performs a right-right (RR) rotation.
   *
   * This rotation is used to rebalance the tree when the right child of the
   * right subtree is too deep, resulting in an imbalance.
   *
   * @param p Pointer to the root of the unbalanced subtree.
   * @return A pointer to the new root of the subtree after rotation.
   */
  TreeNode<T>* RRTurn(TreeNode<T>* p) {
    TreeNode<T>* q = p->right;
    p->balance = 0;
    q->balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
    return p;
  }

  /**
   * @brief Performs a left-right (LR) rotation.
   *
   * This rotation is used when the left subtree is too deep, but the right
   * child of the left subtree is also too deep, causing imbalance.
   *
   * @param p Pointer to the root of the unbalanced subtree.
   * @return A pointer to the new root of the subtree after rotation.
   */
  TreeNode<T>* LRTurn(TreeNode<T>* p) {
    TreeNode<T>* q = p->left;
    TreeNode<T>* r = q->right;

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

  /**
   * @brief Performs a right-left (RL) rotation.
   *
   * This rotation is used when the right subtree is too deep, but the left
   * child of the right subtree is also too deep, causing imbalance.
   *
   * @param p Pointer to the root of the unbalanced subtree.
   * @return A pointer to the new root of the subtree after rotation.
   */
  TreeNode<T>* RLTurn(TreeNode<T>* p) {
    TreeNode<T>* q = p->right;
    TreeNode<T>* r = q->left;

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

  /**
   * @brief Recursively adds a value to the AVL tree and maintains balance.
   *
   * This method adds a value to the AVL tree, adjusting balance factors and
   * performing rotations as necessary to maintain the tree's balance.
   *
   * @param val The value to add.
   * @param p Pointer to the current node in the recursion.
   * @param rost Boolean flag indicating if the tree height increased after
   * insertion.
   * @return A pointer to the current node, possibly updated after rotation.
   */
  TreeNode<T>* add(const T& val, TreeNode<T>* p, bool& rost) {
    if (p == nullptr) {
      p = new TreeNode(val);
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

  /**
   * @brief Performs a right-right rotation with specific balance handling.
   *
   * This is a specialized RR rotation for deletion operations, where balance
   * factors are handled differently.
   *
   * @param p Pointer to the current node.
   * @param umen Boolean flag indicating if the height decreased after deletion.
   * @return A pointer to the new root after rotation.
   */
  TreeNode<T>* RR1Turn(TreeNode<T>* p, bool& umen) {
    TreeNode<T>* q = p->right;
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

  /**
   * @brief Performs a left-left rotation with specific balance handling.
   *
   * This is a specialized LL rotation for deletion operations, where balance
   * factors are handled differently.
   *
   * @param p Pointer to the current node.
   * @param umen Boolean flag indicating if the height decreased after deletion.
   * @return A pointer to the new root after rotation.
   */
  TreeNode<T>* LL1Turn(TreeNode<T>* p, bool& umen) {
    TreeNode<T>* q = p->left;
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

  /**
   * @brief Balances the tree after a left-side deletion.
   *
   * This method checks and adjusts the balance of the tree after a node
   * has been removed from the left subtree.
   *
   * @param p Pointer to the current node.
   * @param umen Boolean flag indicating if the height decreased after deletion.
   * @return A pointer to the updated node after balancing.
   */
  TreeNode<T>* BL(TreeNode<T>* p, bool& umen) {
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

  /**
   * @brief Balances the tree after a right-side deletion.
   *
   * This method checks and adjusts the balance of the tree after a node
   * has been removed from the right subtree.
   *
   * @param p Pointer to the current node.
   * @param umen Boolean flag indicating if the height decreased after deletion.
   * @return A pointer to the updated node after balancing.
   */
  TreeNode<T>* BR(TreeNode<T>* p, bool& umen) {
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

  /**
   * @brief Recursively deletes the maximum node from the left subtree.
   *
   * This method is used to delete the in-order predecessor (maximum value in
   * the left subtree) when deleting a node with two children.
   *
   * @param p Pointer to the node from which to delete the maximum.
   * @param q Pointer to the node being deleted (stores the value to replace).
   * @param umen Boolean flag indicating if the height decreased after deletion.
   */
  void del(TreeNode<T>** p, TreeNode<T>** q, bool& umen) {
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

 public:
  /**
   * @brief Adds a value to the AVL tree.
   *
   * This method provides an interface to add values to the tree and maintain
   * its balance.
   *
   * @param val The value to add.
   */
  void add(const T& val) override {
    bool rost = false;
    this->root = add(val, this->root, rost);
  }
};
