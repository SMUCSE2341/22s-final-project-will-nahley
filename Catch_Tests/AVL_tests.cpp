#include "../catch.hpp"
#include "../data_structures/AVLTree.h"

TEST_CASE("AVL Tree Implementation") {

    SECTION("AVL Node") {
        AVLNode<int> node (5, nullptr, nullptr, 0);
        CHECK(node.left == nullptr);
        CHECK(node.right == nullptr);
        CHECK(node.element == 5);
    }

    SECTION("Case 1 functionality") {
        AVLTree<int> tree;
        tree.insert(3);
        tree.insert(2);
        tree.insert(1);
        tree.insert(4);
        tree.insert(6);

    }

}
