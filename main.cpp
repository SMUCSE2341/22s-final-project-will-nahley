#include <iostream>
#include "AVLTree.h"

int main() {

    AVLTree<int> tree;
    tree.insert(8);
    tree.insert(5);
    tree.insert(3);
    tree.insert(9);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(10);
    tree.insert(1);
    tree.insert(7);

    cout << "Hello" << endl;

    return 0;
}
