#pragma once

#include <print>
#include <vector>

#include "tree.hpp"

template <class T, std::size_t M = 3> class GraphicsBTree;

template <class T, std::size_t M = 3> class BTree : public ITree<T> {
    friend GraphicsBTree<T, M>;

protected:
    struct Node {
        std::vector<T> values;
        std::vector<Node *> child_nodes;

        Node() : values(), child_nodes(1, nullptr) {
            values.reserve(M);
            child_nodes.reserve(M + 1);
        }

        Node(const T &val) : values(1, val), child_nodes(2, nullptr) {}

        std::size_t add(const T &val) {
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

        std::size_t add(const T &val, Node *p) {
            std::size_t I = add(val);
            child_nodes.at(I) = p;
            return I;
        }
    };

    Node *root;
    std::size_t size;

    Node *__newRoot__() {
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

    void __balanced__(Node **cur, Node **prev) {
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

    void __add__(const T &val, Node **cur, Node **prev) {
        for (std::size_t i = 0; i < (*cur)->values.size(); i++) {
            if (val < (*cur)->values.at(i)) {
                if ((*cur)->child_nodes.at(i) == nullptr) (*cur)->add(val);
                else __add__(val, &(*cur)->child_nodes.at(i), cur);
                break;
            } else if (i + 1 == (*cur)->values.size()) {
                if ((*cur)->child_nodes.at(i + 1) == nullptr) (*cur)->add(val);
                else __add__(val, &(*cur)->child_nodes.at(i + 1), cur);
                break;
            }
        }

        if ((*cur)->values.size() == M) {
            if (prev == nullptr) (*cur) = __newRoot__();
            else __balanced__(cur, prev);
        }
    }

    static void __printFromUpToDown__(Node *p) {
        if (p != nullptr) {
            for (const T &val : p->values)
                std::print("{} ", val);
            for (Node *next : p->child_nodes)
                __printFromUpToDown__(next);
        }
    }

    static void __printFromLeftToRight__(Node *p) {
        if (p != nullptr) {
            for (std::size_t i = 0; i < p->values.size(); i++) {
                __printFromLeftToRight__(p->child_nodes.at(i));
                std::print("{} ", p->values.at(i));
            }
            __printFromLeftToRight__(p->child_nodes.back());
        }
    }

    static void __printFromDownToUp__(Node *p) {
        if (p != nullptr) {
            for (Node *next : p->child_nodes)
                __printFromUpToDown__(next);
            for (const T &val : p->values)
                std::print("{} ", val);
        }
    }

    void __clear__(Node *p) {
        if (p == nullptr) return;
        for (Node *&c : p->child_nodes) __clear__(c);
        delete p;
    }

    std::size_t __getSumLenght__(Node *p, std::size_t l) {
        if (p == nullptr) return 0;
        std::size_t sum = p->values.size();
        for (Node *cp : p->child_nodes) sum += __getSumLenght__(cp, l + 1);
        return l + sum;
    }

    std::size_t __getSum__(Node *p) {
        if (p == nullptr) return 0;
        T sum {}, sum_child {};
        for (const T &val : p->values) sum += val;
        for (Node *cp : p->child_nodes) sum_child += __getSum__(cp);
        return sum + sum_child;
    }

    std::size_t __getLevelsCount__(Node *p) {
        if (p == nullptr) return 0;
        std::size_t sum = 0;
        for (Node *cp : p->child_nodes) sum += __getLevelsCount__(cp);
        return sum + 1;
    }

public:
    BTree() : root(nullptr), size(0) {
        if (M < 3)
            throw std::logic_error("Suka, ti che eblan?");
    }

    ~BTree() { clear(); }

    void add(const T &val) {
        if (root == nullptr) root = new Node(val);
        else __add__(val, &root, nullptr);
        size++;
    }

    void printFromUpToDown() {
        __printFromUpToDown__(root);
        std::println();
    }

    void printFromLeftToRight() {
        __printFromLeftToRight__(root);
        std::println();
    }

    void printFromDownToUp() {
        __printFromDownToUp__(root);
        std::println();
    }

    void remove(const T &value) override {}

    void clear() override {
        __clear__(root);
        root = nullptr;
    }

    std::size_t getSize() override { return size; }

    std::size_t getHeight() override {
        std::size_t height = 1;
        Node *p = root;
        while (p->child_nodes.front() != nullptr) {
            p = p->child_nodes.front();
            height++;
        }
        return height;
    }

    double getMediumHeight() override { return static_cast<double>(__getSumLenght__(root, 1)) / static_cast<double>(getSize()); }

    T getSum() override { return __getSum__(root); }

    std::size_t getLevelsCount() { return __getLevelsCount__(root); }
};