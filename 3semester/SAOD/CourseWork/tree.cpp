#include "tree.hpp"
#include <algorithm>

BTreeNode::BTreeNode(bool leaf) : isLeaf(leaf) {}

BTree::BTree(int t) : t(t), root(std::make_unique<BTreeNode>(true)) {}

void BTree::insert(const EmployeeRecord* record) {
    if (root->keys.size() == 2 * t - 1) {
        auto newRoot = std::make_unique<BTreeNode>(false);
        newRoot->children.push_back(std::move(root));
        splitChild(newRoot.get(), 0);
        root = std::move(newRoot);
    }

    insertNonFull(root.get(), record);
}

const EmployeeRecord* BTree::search(int departmentId) const {
    return search(root.get(), departmentId);
}

void BTree::insertNonFull(BTreeNode* node, const EmployeeRecord* record) {
    int key = record->departamentId;
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        node->keys.push_back(0);
        node->records.push_back(nullptr);

        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->records[i + 1] = node->records[i];
            --i;
        }

        node->keys[i + 1] = key;
        node->records[i + 1] = record;
    }
    else {
        while (i >= 0 && key < node->keys[i]) {
            --i;
        }
        ++i;

        if (node->children[i]->keys.size() == 2 * t - 1) {
            splitChild(node, i);
            if (key > node->keys[i]) {
                ++i;
            }
        }

        insertNonFull(node->children[i].get(), record);
    }
}

void BTree::splitChild(BTreeNode* parent, int index) {
    auto fullNode = parent->children[index].get();
    auto newNode = std::make_unique<BTreeNode>(fullNode->isLeaf);

    for (int j = 0; j < t - 1; ++j) {
        newNode->keys.push_back(fullNode->keys[t + j]);
        newNode->records.push_back(fullNode->records[t + j]);
    }

    if (!fullNode->isLeaf) {
        for (int j = 0; j < t; ++j) {
            newNode->children.push_back(std::move(fullNode->children[t + j]));
        }
    }

    parent->keys.insert(parent->keys.begin() + index, fullNode->keys[t - 1]);
    parent->records.insert(parent->records.begin() + index, fullNode->records[t - 1]);
    parent->children.insert(parent->children.begin() + index + 1, std::move(newNode));

    fullNode->keys.resize(t - 1);
    fullNode->records.resize(t - 1);
    fullNode->children.resize(t);
}

const EmployeeRecord* BTree::search(BTreeNode* node, int departmentId) const {
    int i = 0;

    while (i < node->keys.size() && departmentId > node->keys[i]) {
        ++i;
    }

    if (i < node->keys.size() && departmentId == node->keys[i]) {
        return node->records[i];
    }

    if (node->isLeaf) {
        return nullptr;
    }

    return search(node->children[i].get(), departmentId);
}
