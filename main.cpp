#include <iostream>
#include "AVLTree.h"
#include "term.h"
#include "rapidjson/document.h"


#include "catch_setup.h"
#include <unordered_map>

using namespace rapidjson;

int main() {

    AVLTree<Term> words;
    AVLTree<Term> orgs;
    AVLTree<Term> people;

    AVLTree<int> tree;
    tree.insert(78);
    tree.insert(67);
    tree.insert(90);
    tree.insert(50);
    tree.insert(75);
    tree.insert(70);



    return 0;
}
