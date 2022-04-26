#ifndef INC_22S_FINAL_PROJ_AVLTREE_H
#define INC_22S_FINAL_PROJ_AVLTREE_H

#include <cassert>
#include <algorithm>
#include <iostream>
#include <fstream>
// Weiss AVL Implementation - http://www.uoitc.edu.iq/images/documents/informatics-institute/Competitive_exam/DataStructures.pdf

using namespace std;

template <class T>
class AVLNode {
public:
    T element;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;

    AVLNode(const T &theElement, AVLNode<T>* lt, AVLNode<T>* rt, int h = 0) :
        element(theElement), left(lt), right(rt), height(h) {}

};

template <class T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T> *t) const {
        //return t == nullptr ? -1 : t->height;

        if (t == nullptr) {
            return -1;
        }

        return 1 + max(height(t->left), height(t->right));

    }

    void insert(T& x, AVLNode<T>*& t) {
        if (t == nullptr) {
            t = new AVLNode<T> {x, nullptr, nullptr};
        }
        else if (x < t->element) {
            insert(x, t->left);
        } else if (t->element < x) {
            insert(x, t->right);
        }
        balance(t);
    }

    void balance(AVLNode<T>* & t) {
        if (t == nullptr) {
            return;
        }
        if (height(t->left) - height(t->right) > 1) {
            if (height(t->left->left) >= height(t->left->right)) {
                rotateWithLeftChild(t);
            } else {
                doubleWithLeftChild(t);
            }
        } else if (height(t->right) - height(t->left) > 1) {
            if (height(t->right->right) >= height(t->right->left)) {
                rotateWithRightChild(t);
            } else {
                doubleWithRightChild(t);
            }
        }

        t->height = std::max(height(t->left), height(t->right));

    }

    void rotateWithLeftChild(AVLNode<T>* & k2) {
        AVLNode<T>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void rotateWithRightChild(AVLNode<T>* & k1) {
        AVLNode<T>* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(k1->height, height(k2->right));
        k1 = k2;
    }

    void doubleWithLeftChild(AVLNode<T>* & k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    void doubleWithRightChild(AVLNode<T>* & k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightChild(k3);
    }

    AVLNode<T>*& find_node(T &x, AVLNode<T>*& t) {

        if (t == nullptr) {
            return t;
        }

        if (x < t->element) {
            return find_node(x, t->left);
        } else if (t->element < x) {
            return find_node(x, t->right);
        } else if (t->element == x) {
            return t;
        }

    }


    void make_empty(AVLNode<T>*& root) {
        if (root != nullptr) {
            make_empty(root->right);
            make_empty(root->left);
            delete root;
        }

    }

    bool contains(T& x, AVLNode<T>* &t) {
        if (t == nullptr)
            return false;

        if (x < t->element) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else if (t->element == x) {
            return true;
        }

        return false;

    }

    void printIO(AVLNode<T>* x, std::ofstream& out) { //In order traversal
        if (x == nullptr)
            return;

        printIO(x->left, out);

        out << x->element << " ";

        printIO(x->right, out);


    }


public:
    AVLTree<T>() : root(nullptr) {}
    AVLTree<T>(const AVLTree<T> &rhs) : root(nullptr) { *this = rhs; }
    ~AVLTree<T>() { make_empty(); }

    void insert (T &x) {
        insert(x, root);
    }

    AVLNode<T>*& find_node(T &x) {
        return find_node(x, root);
    }


    void make_empty() {
        make_empty(root);
    }

    bool contains(T& x) {
        return contains(x, root);
    }

    void printIO(std::ofstream& out) {
        return printIO(root, out);
    }

};


#endif //INC_22S_FINAL_PROJ_AVLTREE_H
