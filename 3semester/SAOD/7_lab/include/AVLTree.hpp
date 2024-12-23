#pragma once

#include "tree.hpp"

template <class T> struct AVLTreeNode {
    T value;
    AVLTreeNode *left, *right;
    int64_t balance;

    AVLTreeNode(const T &val) : value(val), left(nullptr), right(nullptr), balance(0) {}
};

// The AVL tree
template <class T>
class AVLTree : public BaseTree<T, AVLTreeNode<T>> {
protected:
    AVLTreeNode<T> *LLTurn(AVLTreeNode<T> *p) {
        AVLTreeNode<T> *q = p->left;
        p->balance = 0;
        q->balance = 0;
        p->left = q->right;
        q->right = p;
        p = q;
        return p;
    }

    AVLTreeNode<T> *RRTurn(AVLTreeNode<T> *p) {
        AVLTreeNode<T> *q = p->right;
        p->balance = 0;
        q->balance = 0;
        p->right = q->left;
        q->left = p;
        p = q;
        return p;
    }

    AVLTreeNode<T> *LRTurn(AVLTreeNode<T> *p) {
        AVLTreeNode<T> *q = p->left;
        AVLTreeNode<T> *r = q->right;

        if (r->balance < 0) p->balance = 1;
        else p->balance = 0;

        if (r->balance > 0) q->balance = -1;
        else q->balance = 0;

        r->balance = 0;
        q->right = r->left;
        p->left = r->right;
        r->left = q;
        r->right = p;
        p = r;
        return p;
    }

    AVLTreeNode<T> *RLTurn(AVLTreeNode<T> *p) {
        AVLTreeNode<T> *q = p->right;
        AVLTreeNode<T> *r = q->left;

        if (r->balance > 0) p->balance = -1;
        else p->balance = 0;

        if (r->balance < 0) q->balance = 1;
        else q->balance = 0;

        r->balance = 0;
        q->left = r->right;
        p->right = r->left;
        r->right = q;
        r->left = p;
        p = r;
        return p;
    }

    AVLTreeNode<T> *__add__(const T &val, AVLTreeNode<T> *p, bool &rost) {
        if (p == nullptr) {
            p = new AVLTreeNode(val);
            rost = true;
        } else if (p->value > val) {
            p->left = __add__(val, p->left, rost);
            if (rost) {
                if (p->balance > 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = -1;
                    rost = true;
                } else {
                    if (p->left->balance < 0) p = LLTurn(p);
                    else p = LRTurn(p);
                    rost = false;
                }
            }
        } else {
            p->right = __add__(val, p->right, rost);
            if (rost) {
                if (p->balance < 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = 1;
                    rost = true;
                } else {
                    if (p->right->balance > 0) p = RRTurn(p);
                    else p = RLTurn(p);
                    rost = false;
                }
            }
        }
        return p;
    }

    AVLTreeNode<T> *RR1Turn(AVLTreeNode<T> *p, bool &umen) {
        AVLTreeNode<T> *q = p->right;
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

    AVLTreeNode<T> *LL1Turn(AVLTreeNode<T> *p, bool &umen) {
        AVLTreeNode<T> *q = p->left;
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

    AVLTreeNode<T> *BL(AVLTreeNode<T> *p, bool &umen) {
        if (p->balance == -1) p->balance = 0;
        else if (p->balance == 0) {
            p->balance = 1;
            umen = false;
        } else if (p->balance == 1) {
            if (p->right->balance >= 0) p = RR1Turn(p, umen);
            else p = RLTurn(p);
        }
        return p;
    }

    AVLTreeNode<T> *BR(AVLTreeNode<T> *p, bool &umen) {
        if (p->balance == 1) p->balance = 0;
        else if (p->balance == 0) {
            p->balance = -1;
            umen = false;
        } else if (p->balance == -1) {
            if (p->left->balance <= 0) p = LL1Turn(p, umen);
            else p = LRTurn(p);
        }
        return p;
    }

    void del(AVLTreeNode<T> **p, AVLTreeNode<T> **q, bool &umen) {
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

    AVLTreeNode<T> *__remove__(const T &val, AVLTreeNode<T> *p, bool &umen) {
        if (p == nullptr) {
        } else if (val < p->value) {
            p->left = __remove__(val, p->left, umen);
            if (umen) p = BL(p, umen);
        } else if (val > p->value) {
            p->right = __remove__(val, p->right, umen);
            if (umen) p = BR(p, umen);
        } else {
            AVLTreeNode<T> *q = p;
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
    void add(const T &val) override {
        bool rost = false;
        this->root = __add__(val, this->root, rost);
    }

    void remove(const T &val) override {
        bool umen = false;
        this->root = __remove__(val, this->root, umen);
    }
};