#ifndef INC_22S_FINAL_PROJ_INDEXHANDLER_H
#define INC_22S_FINAL_PROJ_INDEXHANDLER_H

#include <vector>
#include <string>
#include <iostream>
#include "data_structures/AVLTree.h"
#include "data_structures/HashTable.h"
#include "Term.h"
#include "Parser.h"
#include <chrono>

class IndexHandler {
public:
    IndexHandler(char* search_string, char* search_path);
    void generate_filenames();

    //Populates AVL Tree
    void add_terms(std::vector<std::string>& stemmed_words, std::string docID);
    void populate_tree();

    //Based off of search string
    vector<string> get_correct_documents();

private:
    string search_string;
    string search_path;
    vector<string> filename_vec;

    AVLTree<Term> terms_tree;


};


#endif //INC_22S_FINAL_PROJ_INDEXHANDLER_H
