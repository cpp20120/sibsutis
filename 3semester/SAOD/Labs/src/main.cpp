
#include <Windows.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "../include/avl_tree.hpp"
#include "../include/b_tree.hpp"
#include "../include/base_tree.hpp"
#include "../include/coding.hpp"
#include "../include/os_tree.hpp"
#include "../include/pbs_tree.hpp"
#include "../include/rs_tree.hpp"
#include <set>

/**
 *      1
         \
          3
         / \
        2   5
           / \
          4   6

          3 + 3 + 2 + 2 + 1 = 11
          11/6 = 1.83

8 вариант
 */
void Lab1() {
  RSTree<int> tree;
  tree.Add(1);
  tree.Add(3);
  tree.Add(2);
  tree.Add(5);
  tree.Add(4);
  tree.Add(6);

  std::print("Pre-order: ");
  tree.PrintPreOrder();
  std::print("In-order: ");
  tree.PrintInOrder();
  std::print("Post-order: ");
  tree.PrintPostOrder();

  std::println("Tree size: {}", tree.Size());
  std::println("Tree sum: {}", tree.Sum());
  std::println("Tree height: {}", tree.Height());
  std::println("Tree average height: {:.2f}", tree.AverageHeight());
}

/**
 *   4
    / \
   2   5
  / \   \
 1   3   6
 *
 */
void Lab2() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr(100);
  for (int i = 0; i < 100; i++) {
    arr[i] = dis(gen);
  }

  PBSTree<int> tree(arr);

  std::print("In-order: ");
  tree.PrintInOrder();

  std::println("Tree size: {}", tree.Size());
  std::println("Tree sum: {}", tree.Sum());
  std::println("Tree height: {}", tree.Height());
  std::println("Tree average height: {:.2f}", tree.AverageHeight());
}

void Lab3() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr;
  for (int i = 0; i < 100; i++) {
    arr.push_back(dis(gen));
  }

  RSTree<int> rs_tree;
  for (int i = 0; i < 100; i++) {
    rs_tree.Add(arr[i]);
  }

  PBSTree<int> pbs_tree(arr);

  std::print("In-order: ");
  rs_tree.PrintInOrder();

  std::println("\n n = 100 | Size | Sum | Height | Average Height");
  std::println("-----------------------------------------------");
  std::println("    PBST |{:5} |{:4} |{:7} |{:14.2f}", pbs_tree.Size(),
               pbs_tree.Sum(), pbs_tree.Height(), pbs_tree.AverageHeight());
  std::println("     RST |{:5} |{:4} |{:7} |{:14.2f}", rs_tree.Size(),
               rs_tree.Sum(), rs_tree.Height(), rs_tree.AverageHeight());

  // Test AVL tree for comparison
  AVLTree<int> avl_tree;
  for (int i = 0; i < 100; i++) {
    avl_tree.Add(arr[i]);
  }
  std::println("     AVL |{:5} |{:4} |{:7} |{:14.2f}", avl_tree.Size(),
               avl_tree.Sum(), avl_tree.Height(), avl_tree.AverageHeight());
}

void Lab4() {
  RSTree<int> tree;
  std::vector<int> arr(10);

  std::println("Enter 10 integers:");
  for (int& elem : arr) {
    std::cin >> elem;
    tree.Add(elem);
  }

  tree.PrintInOrder();

  for (int elem : arr) {
    tree.Remove(elem);
    tree.PrintInOrder();
  }
}

/**
 *  7, 2, 9, 1, 5, 8, 3, 6, 4, 12
 *       7
       /   \
      3     9
     / \   /  \
    2  5  8    12
   /  / \
  1   4   6
 */
void Lab5() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  AVLTree<int> avl_tree;
  PBSTree<int> pbs_tree;
  RSTree<int> rs_tree;
  std::vector<int> arr;

  std::set<int> unique_values;
  int duplicates = 0;

  for (int i = 0; i < 100; i++) {
    int value = dis(gen);
    arr.push_back(value);

    if (unique_values.find(value) != unique_values.end()) {
      duplicates++;
    }
    unique_values.insert(value);

    avl_tree.Add(value);
    pbs_tree.Add(value);
    rs_tree.Add(value);
  }

  std::println("Generated {} values with {} duplicates", 100, duplicates);
  std::print("AVL in-order: ");
  avl_tree.PrintInOrder();

  std::println("\n n = 100 | Size | Sum | Height | Average Height");
  std::println("-------------------------------------------------");
  std::println("     PBS |{:5} |{:4} |{:7} |{:14.2f} ", pbs_tree.Size(),
               pbs_tree.Sum(), pbs_tree.Height(), pbs_tree.AverageHeight());
  std::println("     RST |{:5} |{:4} |{:7} |{:14.2f} ", rs_tree.Size(),
               rs_tree.Sum(), rs_tree.Height(), rs_tree.AverageHeight() );
  std::println("     AVL |{:5} |{:4} |{:7} |{:14.2f} ", avl_tree.Size(),
               avl_tree.Sum(), avl_tree.Height(), avl_tree.AverageHeight()
               );

  //std::println("\nAVL Tree Balance Factor: {}", avl_tree.GetBalance());

  //  AVLTree<int> test_tree;
  //std::vector<int> test_values = {10, 20, 30, 40, 50, 25};
  //for (int val : test_values) {
  //  test_tree.Add(val);
  //}

  //std::println("\nTest AVL tree (values 10,20,30,40,50,25):");
  //std::println("Height: {}, Balanced: {}, Balance Factor: {}",
  //             test_tree.Height(), test_tree.IsBalanced() ? "Yes" : "No",
  //             test_tree.GetBalance());
  //std::print("In-order: ");
  //test_tree.PrintInOrder();

}
void Lab_removeRSTree() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr(100);
  for (int i = 0; i < 100; i++) {
    arr[i] = dis(gen);
  }

  RSTree<int> rs_tree;

  for (int value : arr) {
    rs_tree.AddImpl(value);
  }

  std::println("Initial tree size: {}", rs_tree.Size());
  std::println("Total values added: {}", arr.size());

  std::print("\nInitial tree (in-order): ");
  rs_tree.PrintInOrder();
  std::println("");

  std::println("Initial tree height: {}", rs_tree.Height());

  std::vector<int> values_to_remove;
  for (int i = 0; i < 5; i++) {
    int index = dis(gen) % arr.size();
    if (index < 0) index = -index;
    values_to_remove.push_back(arr[index]);
  }

  values_to_remove.push_back(150);
  values_to_remove.push_back(-150);

  std::println("\n--- Removing specific values ---");
  for (int value : values_to_remove) {
    bool existed_before = rs_tree.Contains(value);
    size_t size_before = rs_tree.Size();

    rs_tree.RemoveImpl(value);

    bool exists_after = rs_tree.Contains(value);
    size_t size_after = rs_tree.Size();

    std::println("Removing value: {} (existed: {}) -> after: {}, size: {}->{}",
                 value, existed_before ? "Yes" : "No",
                 exists_after ? "Still exists" : "Removed", size_before,
                 size_after);
  }

  std::println("\n--- After specific removals ---");
  std::println("Tree size: {}", rs_tree.Size());
  std::println("Tree height: {}", rs_tree.Height());
  std::print("Tree (in-order): ");
  rs_tree.PrintInOrder();
  std::println("");

  std::println("\n--- Removing all elements gradually ---");
  while (!rs_tree.Empty()) {
    std::vector<int> temp_elements = rs_tree.GetInOrderElements();

    if (!temp_elements.empty()) {
      int value_to_remove = temp_elements[0];
      size_t size_before = rs_tree.Size();

      rs_tree.RemoveImpl(value_to_remove);

      size_t size_after = rs_tree.Size();

      std::println("Removed {}  Size: {}->{}, Height: {}", value_to_remove,
                   size_before, size_after, rs_tree.Height());
    }
  }

  std::println("\n--- Final state ---");
  std::println("Final tree size: {}", rs_tree.Size());
  std::println("Tree is empty: {}", rs_tree.Empty() ? "Yes" : "No");
}

void Lab_remove_PBSTree() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(-100, 100);

  std::vector<int> arr(100);
  for (int i = 0; i < 100; i++) {
    arr[i] = dis(gen);
  }

  PBSTree<int> pbs_tree(arr);

  std::println(" PBSTree Remove Test ===");
  std::println("Initial tree size: {}", pbs_tree.Size());
  std::println("Total values generated: {}", arr.size());

  std::print("\nInitial tree (in-order): ");
  pbs_tree.PrintInOrder();
  std::println("");

  std::println("Initial tree height: {}", pbs_tree.Height());

  std::vector<int> values_to_remove;
  for (int i = 0; i < 5; i++) {
    int index = dis(gen) % arr.size();
    if (index < 0) index = -index;
    values_to_remove.push_back(arr[index]);
  }

  values_to_remove.push_back(150);
  values_to_remove.push_back(-150);

  for (int value : values_to_remove) {
    bool existed_before = pbs_tree.Contains(value);

    pbs_tree.RemoveImpl(value); 

    bool exists_after = pbs_tree.Contains(value);
    std::println("Removing value: {} (existed: {}) -> after removal: {}", value,
                 existed_before ? "Yes" : "No",
                 exists_after ? "Still exists" : "Removed");
  }

  std::println("Final tree size: {}", pbs_tree.Size());
  std::println("Final tree height: {}", pbs_tree.Height());

  std::print("Final tree ");
  pbs_tree.PrintInOrder();
  std::println("");

  auto all_elements = pbs_tree.ToVector();
  for (size_t i = 0; i < all_elements.size(); i++) {
    int value = all_elements[i];
    pbs_tree.Remove(value);

    if (pbs_tree.Size() > 0) {
      std::println("Removed {}  Size: {}, Height: {}", value, pbs_tree.Size(),
                   pbs_tree.Height());
    } else {
      std::println("Removed {}  Size: {}", value, pbs_tree.Size());
    }
  }

  std::println("\nFinal tree size after removing all: {}", pbs_tree.Size());
  std::println("Tree is empty: {}", pbs_tree.Empty() ? "Yes" : "No");
}

void Lab6() {
  AVLTree<int> tree;
  std::vector<int> arr(10);

  std::println("Enter 10 integers:");
  for (int& elem : arr) {
    std::cin >> elem;
    tree.Add(elem);
  }

  std::println("Initial tree:");
  tree.PrintInOrder();
  std::println("Height: {}, Balanced: {}, Balance Factor: {}", tree.Height(),
               tree.IsBalanced() ? "Yes" : "No", tree.GetBalance());

  for (int elem : arr) {
    tree.Remove(elem);
    std::print("After removing {}: ", elem);
    tree.PrintInOrder();
    std::println("Height: {}, Balanced: {}, Balance Factor: {}", tree.Height(),
                 tree.IsBalanced() ? "Yes" : "No", tree.GetBalance());
  }
}

void Lab7() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(1, 1000);

  BTree<int, 10> b_tree;
  BTree<int, 3> dbd_tree;  // DBD
  AVLTree<int> avl_tree;

  std::vector<int> deterministic_values;
  std::vector<int> random_values;

  for (int i = 0; i < 100; i++) {
    deterministic_values.push_back(i);
  }

  for (int i = 0; i < 100; i++) {
    random_values.push_back(dist(gen));
  }

  std::sort(random_values.begin(), random_values.end());
  random_values.erase(std::unique(random_values.begin(), random_values.end()),
                      random_values.end());

  while (random_values.size() < 100) {  // 100 unique
    int new_val = dist(gen);
    if (std::find(random_values.begin(), random_values.end(), new_val) ==
        random_values.end()) {
      random_values.push_back(new_val);
    }
  }

  std::println(" Testing with Deterministic Sequence (0-99) ===");

  for (int i = 0; i < 100; i++) {
    b_tree.Add(deterministic_values[i]);
    dbd_tree.Add(deterministic_values[i]);
    avl_tree.Add(deterministic_values[i]);
  }

  std::println(" Initial State ===");
  std::print("B-tree in-order: ");
  b_tree.PrintInOrder();
  std::print("DBD-tree in-order: ");
  dbd_tree.PrintInOrder();
  std::print("AVL tree in-order: ");
  avl_tree.PrintInOrder();

  std::println("\n n = 100 | Size | Sum | Height | Average Height");
  std::println("-------------------------------------------------");
  std::println("     AVL |{:5} |{:5} |{:7} |{:14.2f}", avl_tree.Size(),
               avl_tree.Sum(), avl_tree.Height(), avl_tree.AverageHeight());
  std::println("   B-tree|{:5} |{:5} |{:7} |{:14.2f}", b_tree.Size(),
               b_tree.Sum(), b_tree.Height(), b_tree.AverageHeight());
  std::println("     DBD |{:5} |{:5} |{:7} |{:14.2f}", dbd_tree.Size(),
               dbd_tree.Sum(), dbd_tree.Height(), dbd_tree.AverageHeight());

  std::vector<int> elements_to_remove = {5, 10, 15, 3, 8, 12, 18, 1, 7, 14};

  std::println("\n Step-by-step removal ===");

  for (size_t i = 0; i < elements_to_remove.size(); i++) {
    int elem = elements_to_remove[i];

    std::println("\nStep {}: Removing element {}", i + 1, elem);

    bool b_exists = b_tree.Contains(elem);
    bool dbd_exists = dbd_tree.Contains(elem);
    bool avl_exists = avl_tree.Contains(elem);

    if (b_exists) {
      b_tree.Remove(elem);
      std::print("B-tree after removing {}: ", elem);
      b_tree.PrintInOrder();
    }

    if (dbd_exists) {
      dbd_tree.Remove(elem);
      std::print("DBD after removing {}: ", elem);
      dbd_tree.PrintInOrder();
    }

    if (avl_exists) {
      avl_tree.Remove(elem);
      std::print("AVL after removing {}: ", elem);
      avl_tree.PrintInOrder();
      std::println("Balance Factor: {}", avl_tree.GetBalance());
    }

    if ((i + 1) % 3 == 0) {
      std::println("\n--- Comparison after {} removals ---", i + 1);
      std::println("B-tree  - Size: {}, Height: {}, Avg Height: {:.2f}",
                   b_tree.Size(), b_tree.Height(), b_tree.AverageHeight());
      std::println("DBD-tree - Size: {}, Height: {}, Avg Height: {:.2f}",
                   dbd_tree.Size(), dbd_tree.Height(),
                   dbd_tree.AverageHeight());
      std::println("AVL tree - Size: {}, Height: {}, Avg Height: {:.2f}",
                   avl_tree.Size(), avl_tree.Height(),
                   avl_tree.AverageHeight());
    }
  }

  std::println("\n Final State (Deterministic) ===");
  std::print("B-tree final: ");
  b_tree.PrintInOrder();
  std::print("DBD-tree final: ");
  dbd_tree.PrintInOrder();
  std::print("AVL tree final: ");
  avl_tree.PrintInOrder();

  std::println("\nFinal statistics (Deterministic):");
  std::println("B-tree  - Size: {}, Height: {}, Avg Height: {:.2f}",
               b_tree.Size(), b_tree.Height(), b_tree.AverageHeight());
  std::println("DBD-tree - Size: {}, Height: {}, Avg Height: {:.2f}",
               dbd_tree.Size(), dbd_tree.Height(), dbd_tree.AverageHeight());
  std::println("AVL tree - Size: {}, Height: {}, Avg Height: {:.2f}",
               avl_tree.Size(), avl_tree.Height(), avl_tree.AverageHeight());

  b_tree.Clear();
  dbd_tree.Clear();
  avl_tree.Clear();

  std::println("\n\n Testing with Random Sequence:");

  for (int i = 0; i < 100; i++) {
    b_tree.Add(random_values[i]);
    dbd_tree.Add(random_values[i]);
    avl_tree.Add(random_values[i]);
  }

  std::println(" Initial State (Random):");
  std::print("B-tree in-order (first 20): ");
  b_tree.PrintInOrder();  
  std::print("DBD-tree in-order (first 20): ");
  dbd_tree.PrintInOrder();
  std::print("AVL tree in-order (first 20): ");
  avl_tree.PrintInOrder();

  std::println("\n n = 100 | Size | Sum | Height | Average Height");
  std::println("-------------------------------------------------");
  std::println("     AVL |{:5} |{:5} |{:7} |{:14.2f}", avl_tree.Size(),
               avl_tree.Sum(), avl_tree.Height(), avl_tree.AverageHeight());
  std::println("   B-tree|{:5} |{:5} |{:7} |{:14.2f}", b_tree.Size(),
               b_tree.Sum(), b_tree.Height(), b_tree.AverageHeight());
  std::println("     DBD |{:5} |{:5} |{:7} |{:14.2f}", dbd_tree.Size(),
               dbd_tree.Sum(), dbd_tree.Height(), dbd_tree.AverageHeight());

  std::vector<int> random_removal_values;
  std::sample(random_values.begin(), random_values.end(),
              std::back_inserter(random_removal_values), 10, gen);

  std::println("\nStep-by-step removal (Random)");
  std::print("Removing values: ");
  for (size_t i = 0; i < random_removal_values.size(); ++i) {
    std::print("{}{}", random_removal_values[i],
               (i == random_removal_values.size() - 1) ? "" : ", ");
  }
  std::println("");

  for (size_t i = 0; i < random_removal_values.size(); i++) {
    int elem = random_removal_values[i];

    std::println("\nStep {}: Removing element {}", i + 1, elem);

    bool b_exists = b_tree.Contains(elem);
    bool dbd_exists = dbd_tree.Contains(elem);
    bool avl_exists = avl_tree.Contains(elem);

    if (b_exists) {
      b_tree.Remove(elem);
      std::print("B-tree after removing {}: ", elem);
      b_tree.PrintInOrder();
    }

    if (dbd_exists) {
      dbd_tree.Remove(elem);
      std::print("DBD after removing {}: ", elem);
      dbd_tree.PrintInOrder();
    }

    if (avl_exists) {
      avl_tree.Remove(elem);
      std::print("AVL after removing {}: ", elem);
      avl_tree.PrintInOrder();
      std::println("Balance Factor: {}", avl_tree.GetBalance());
    }

    if ((i + 1) % 3 == 0) {
      std::println("\n--- Comparison after {} removals (Random) ---", i + 1);
      std::println("B-tree  - Size: {}, Height: {}, Avg Height: {:.2f}",
                   b_tree.Size(), b_tree.Height(), b_tree.AverageHeight());
      std::println("DBD-tree - Size: {}, Height: {}, Avg Height: {:.2f}",
                   dbd_tree.Size(), dbd_tree.Height(),
                   dbd_tree.AverageHeight());
      std::println("AVL tree - Size: {}, Height: {}, Avg Height: {:.2f}",
                   avl_tree.Size(), avl_tree.Height(),
                   avl_tree.AverageHeight());
    }
  }

  std::println("\n Final State (Random):");
  std::print("B-tree final: ");
  b_tree.PrintInOrder();
  std::print("DBD-tree final: ");
  dbd_tree.PrintInOrder();
  std::print("AVL tree final: ");
  avl_tree.PrintInOrder();

  std::println("\nFinal statistics (Random):");
  std::println("B-tree  - Size: {}, Height: {}, Avg Height: {:.2f}",
               b_tree.Size(), b_tree.Height(), b_tree.AverageHeight());
  std::println("DBD-tree - Size: {}, Height: {}, Avg Height: {:.2f}",
               dbd_tree.Size(), dbd_tree.Height(), dbd_tree.AverageHeight());
  std::println("AVL tree - Size: {}, Height: {}, Avg Height: {:.2f}",
               avl_tree.Size(), avl_tree.Height(), avl_tree.AverageHeight());

  std::println("\n Comparison: Deterministic vs Random:");
  std::println("Tree performance comparison:");
  std::println("Deterministic (0-99) insertion vs Random insertion");
  std::println(
      "Note: Random insertion typically tests balancing algorithms better");
}
/**
 *     4
      / \
     /   \
    2     5
   / \     \
  1   3     6
 /
0
 * 
 */
/**
void Lab8() {
  SetConsoleOutputCP(CP_UTF8);
  
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  const std::size_t size = 7;
  std::vector<std::pair<int, uint64_t>> arr;

  for (int i = 0; i < size; i++) {
    arr.push_back({i, dis(gen)});
  }

  std::print("Base array: ");
  for (const auto& elem : arr) std::print("{} ", elem.first);
  std::println();

  std::print("Weights: ");
  for (const auto& elem : arr) std::print("{} ", elem.second);
  std::println("\n");

  EOSTree<int> eost_tree(arr);
  std::print("Tree in-order: ");
  eost_tree.PrintInOrder();

  std::println("AW matrix:");
  eost_tree.PrintAW();

  std::println("AP matrix:");
  eost_tree.PrintAP();

  std::println("AR matrix:");
  eost_tree.PrintAR();

  std::println("\nAP[0,size] / AW[0,size] = {:.3f}",
               static_cast<double>(eost_tree.GetAP()[0][size]) /
                   eost_tree.GetAW()[0][size]);

  std::println("Weighted average height: {:.3f}",
               eost_tree.GetWeightedAverageHeight());

  std::println("\n n = {:3} | Size | Sum | Height | Average Height", size);
  std::println("-----------------------------------------------");
  std::println("     EOS |{:5} |{:4} |{:7} |{:14.2f}", eost_tree.Size(),
               eost_tree.Sum(), eost_tree.Height(), eost_tree.AverageHeight());
}     */ 

void Lab8() {
  SetConsoleOutputCP(CP_UTF8);
  /*
  * 
  * OST
  *       2(weight=2)
          /    \
  1(weight=5)  4(weight=1)
               /
            3(weight=1)
    A1
      1(weight=5)
       \
        2(weight=2)
         \
          3(weight=1)
           \
            4(weight=1)


   A2
        2(2)
       /  \
     1(5) 3(1)
           \
           4(1)
  */

  const std::size_t size = 6; 
  std::vector<std::pair<int, uint64_t>> arr;

  std::vector<int> random_values = {1, 2,3, 4, 5,6,};
  std::vector<uint64_t> weights = {8, 3, 12, 1, 5, 10};

  for (int i = 0; i < size; i++) {
    arr.push_back({random_values[i], weights[i]});
  }

  std::print("Base array: ");
  for (const auto& elem : arr) std::print("{} ", elem.first);
  std::println();

  std::print("Weights: ");
  for (const auto& elem : arr) std::print("{} ", elem.second);
  std::println("\n");

  EOSTree<int> eost_tree(arr);
  std::print("Tree in-order: ");
  eost_tree.PrintInOrder();

  std::println("AW matrix:");
  eost_tree.PrintAW();

  std::println("AP matrix:");
  eost_tree.PrintAP();

  std::println("AR matrix:");
  eost_tree.PrintAR();

  std::println("\nAP[0,size] / AW[0,size] = {:.3f}",
               static_cast<double>(eost_tree.GetAP()[0][size]) /
                   eost_tree.GetAW()[0][size]);

  std::println("Weighted average height: {:.3f}",
               eost_tree.GetWeightedAverageHeight());

  std::println("\n n = {:3} | Size | Sum | Height | Average Height", size);
  std::println("-----------------------------------------------");
  std::println("     EOS |{:5} |{:4} |{:7} |{:14.2f}", eost_tree.Size(),
               eost_tree.Sum(), eost_tree.Height(), eost_tree.AverageHeight());

  std::println("\n=== Random data ===");

  std::vector<std::pair<int, uint64_t>> random_arr;
  std::srand(std::time(nullptr));

  const std::size_t random_size = 6;
  for (int i = 0; i < random_size; i++) {
    int random_val = std::rand() % 100 + 1;         
    uint64_t random_weight = static_cast<uint64_t>(std::rand() % 15) + 1;  
    random_arr.push_back({random_val, random_weight});
  }

  std::print("Random array: ");
  for (const auto& elem : random_arr) std::print("{} ", elem.first);
  std::println();

  std::print("Random weights: ");
  for (const auto& elem : random_arr) std::print("{} ", elem.second);
  std::println("\n");

  EOSTree<int> random_eost_tree(random_arr);
  std::print("Random tree in-order: ");
  random_eost_tree.PrintInOrder();

  std::println("Weighted average height: {:.3f}",
               random_eost_tree.GetWeightedAverageHeight());

  std::println("\nA1 vs A2");

  OSTreeA1<int> a1_tree(arr);
  OSTreeA2<int> a2_tree(arr);

  std::println("A1 Tree (sorted by weight):");
  a1_tree.PrintInOrder();

  std::println("A2 Tree (balanced by weight):");
  a2_tree.PrintInOrder();

  std::println("\nComparison for main array:");
  std::println("Type     | Size | Height | Avg Height | Weighted Avg Height");
  std::println("-----------------------------------------------------------");
  std::println("EOS Tree |{:5} |{:7} |{:12.2f} |{:19.3f}", eost_tree.Size(),
               eost_tree.Height(), eost_tree.AverageHeight(),
               eost_tree.GetWeightedAverageHeight());
  std::println("A1 Tree  |{:5} |{:7} |{:12.2f}", a1_tree.Size(),
               a1_tree.Height(), a1_tree.AverageHeight());
  std::println("A2 Tree  |{:5} |{:7} |{:12.2f}", a2_tree.Size(),
               a2_tree.Height(), a2_tree.AverageHeight());
}

void Lab9() {
  SetConsoleOutputCP(CP_UTF8);

  const int size = 100;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, size);

  std::vector<std::pair<int, uint64_t>> arr;
  for (int i = 0; i < size; i++) {
    arr.push_back({i, dis(gen)});
  }

  EOSTree<int> eost_tree(arr);
  OSTreeA1<int> a1_tree(arr);
  OSTreeA2<int> a2_tree(arr);

  std::print("A1 tree in-order: ");
  a1_tree.PrintInOrder();

  std::print("A2 tree in-order: ");
  a2_tree.PrintInOrder();

  std::println("\n n = {:3} | Size | Sum | Height | Average Height|  Avg Weighted Height", size);
  std::println("-----------------------------------------------");
  std::println("     EOS |{:5} |{:4} |{:7} |{:14.2f}| {:14.2f}", eost_tree.Size(),
               eost_tree.Sum(), eost_tree.Height(), eost_tree.AverageHeight(), eost_tree.GetWeightedAverageHeight());
  std::println("      A1 |{:5} |{:4} |{:7} |{:14.2f}| {:14.2f}", a1_tree.Size(),
               a1_tree.Sum(), a1_tree.Height(), a1_tree.AverageHeight(),a1_tree.GetWeightedAverageHeight());
  std::println("      A2 |{:5} |{:4} |{:7} |{:14.2f}| {:14.2f}", a2_tree.Size(),
               a2_tree.Sum(), a2_tree.Height(), a2_tree.AverageHeight(),
               a2_tree.GetWeightedAverageHeight());
}

void Lab11(std::vector<coding::Table>& alphabet,
           std::vector<coding::Table>& str) {
  coding::FanoA2(alphabet);

  std::size_t max_length = 0;
  for (const coding::Table& table : alphabet) {
    if (max_length < table.code.size()) {
      max_length = table.code.size();
    }
  }

  std::println(" Char | Probability |   Code | Length");
  std::println("-------------------------------------");

  for (const coding::Table& table : alphabet) {
    std::string code_str;
    for (int bit : table.code) {
      code_str += std::to_string(bit);
    }

    std::println(" {:>4} | {:11.6f} | {:>{}} | {:6}", table.symbol,
                 table.probability, code_str, max_length, table.code.size());
  }

  double sum = 0.0;
  for (const coding::Table& table : alphabet) {
    sum += 1.0 / std::pow(2.0, table.code.size());
  }

  double avg_length = coding::CalculateAverageCodeLength(alphabet);
  double entropy = coding::CalculateEntropy(alphabet);
  double redundancy = avg_length - entropy;

  std::println("\nKraft inequality: {:.6f} <= 1", sum);
  std::println("Entropy: {:.6f}", entropy);
  std::println("Average code length: {:.6f}", avg_length);
  std::println("Redundancy: {:.6f}", redundancy);

  std::print("\nText: ");
  for (coding::Table& s : str) {
    for (coding::Table& t : alphabet) {
      if (s.symbol == t.symbol) {
        s.code = t.code;
        break;
      }
    }
    std::print("{}", s.symbol);
  }

  std::print("\nCode: ");
  std::size_t code_size = 0;
  for (const coding::Table& s : str) {
    for (int bit : s.code) {
      std::print("{}", bit);
      code_size++;
    }
  }

  std::println("\nOriginal size: 800 bits");
  std::println("Encoded size: {} bits", code_size);
  std::println("Compression ratio: {:.3f}",
               static_cast<double>(code_size) / 800.0);
}

void Lab10_13() {
  SetConsoleOutputCP(CP_UTF8);

  const std::string file_name = "chars.txt";
  const int file_size = 10240;

  std::vector<coding::Table> alphabet;
  for (char c = 'a'; c <= 'z'; c++) {
    alphabet.push_back({static_cast<int>(c), 0.0});
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

  std::ofstream file_out(file_name);
  for (int i = 0; i < file_size; i++) {
    char c = alphabet[dis(gen)].symbol;
    file_out << c;
  }
  file_out.close();

  std::ifstream file_in(file_name);
  char c;
  int total_chars = 0;

  while (file_in.get(c)) {
    for (coding::Table& symbol : alphabet) {
      if (c == symbol.symbol) {
        symbol.probability += 1.0;
        total_chars++;
        break;
      }
    }
  }
  file_in.close();

  for (coding::Table& symbol : alphabet) {
    symbol.probability /= total_chars;
  }

  std::print("Shennon: \n");
  coding::Shennon(alphabet);    // Lab 10
  //std::print("Fano: \n");
  //coding::Fano(alphabet);       // Lab 11
  //std::print("Huffman: \n");
  //coding::Huffman(alphabet);  // Lab 12
  // std::print("GilbertMur: \n"); 
  // coding::GilbertMur(alphabet); // Lab 13

  coding::PrintCodes(alphabet);

  std::vector<coding::Table> test_string;
  for (int i = 0; i < 100; i++) {
    test_string.push_back(alphabet[dis(gen)]);
  }

  Lab11(alphabet, test_string);
}

void Lab14() {
  SetConsoleOutputCP(CP_UTF8);

  std::string text =
      "December is a magical month when the boundaries between reality and "
      "fairy tales are blurred, and s   now, like a fluffy feather bed, covers "
      "the earth.";
  std::string word = "snow";

  std::println("Text: {}", text);
  std::println("Word: {}", word);

  auto [naivePositions, naiveCompares] = coding::NaiveSearch(text, word);
  std::print("Simple search indexes: ");
  for (auto idx : naivePositions) std::print("{} ", idx);
  std::println("\nCompares: {}", naiveCompares);

  auto [rkPositions, rkCompares] = coding::RabinKarp(text, word);
  std::print("Rabin-Karp indexes: ");
  for (auto idx : rkPositions) std::print("{} ", idx);
  std::println("\nCompares: {}", rkCompares);
}

int main() {
  std::println("=== Data Structures and Algorithms Labs ===\n");

  //std::println("Lab 1 - Basic Binary Tree");
  //Lab1();

  //std::println("\nLab 2 - Perfectly Balanced Tree");
  //Lab2();

 //std::println("\nLab 3 - Random search tree build");
 //Lab3();

  //std::println("\n Remove from PBS tree");
  //Lab_remove_PBSTree();

  //std::print("\n Remove from RST tree");
  //Lab_removeRSTree();

  // std::println("\nLab 4 - Random search Tree Remove Operations");
  // Lab4();

  //std::println("\nLab 5 - AVL Tree");
  //Lab5();

  // std::println("\nLab 6 - AVL Tree Operations");
  // Lab6();

  //std::println("\nLab 7 - B-tree");
  //Lab7();

  //std::println("\nLab 8 - Optimal Search Tree");
  //Lab8();

  //std::println("\nLab 9 - OST Algorithms Comparison");
  //Lab9();

  // std::println("\nLabs 10-13 - Coding Algorithms");
  // Lab10_13();

  // std::println("\nLab 14 - String Search");
  // Lab14();

  return 0;
}