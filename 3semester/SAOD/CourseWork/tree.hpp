#pragma once

#include "db.hpp"
#include <vector>
#include <memory>

struct BTreeNode {
    bool isLeaf;
    std::vector<int> keys;
    std::vector<const EmployeeRecord*> records; 
    std::vector<std::unique_ptr<BTreeNode>> children; 

    explicit BTreeNode(bool leaf);
};

class BTree {
public:
    explicit BTree(int t);
    void insert(const EmployeeRecord* record);
    const EmployeeRecord* search(int departmentId) const;

private:
    int t; // минимальный порядок дерева
    std::unique_ptr<BTreeNode> root;

    void insertNonFull(BTreeNode* node, const EmployeeRecord* record);
    void splitChild(BTreeNode* parent, int index);
    const EmployeeRecord* search(BTreeNode* node, int departmentId) const;
};
