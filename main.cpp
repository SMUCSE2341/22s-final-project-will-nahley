#include <iostream>
#include "AVLTree.h"

#include "catch_setup.h"

int main() {


    AVLTree<int> tree;
    tree.insert(78);
    tree.insert(67);
    tree.insert(90);
    tree.insert(50);
    tree.insert(75);
    tree.insert(70);

    cout << "Hello" << endl;

    return 0;
}
