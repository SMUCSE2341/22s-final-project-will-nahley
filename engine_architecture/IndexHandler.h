#ifndef INC_22S_FINAL_PROJ_INDEXHANDLER_H
#define INC_22S_FINAL_PROJ_INDEXHANDLER_H

#include <vector>
#include <string>
#include <iostream>
#include "../data_structures/AVLTree.h"
#include "../data_structures/HashTable.h"
#include "../Term.h"
#include "Parser.h"
#include <chrono>

class IndexHandler {
public:
    IndexHandler(string search_string,string search_path);
    void generate_filenames();

    //Populates AVL Tree
    void add_terms(std::vector<std::string>& stemmed_words, std::string docID);
    void populate_tree();

    //Based off of search string
    vector<string> get_correct_documents();
    vector<string> get_org_documents();
    vector<string> get_person_documents();


private:
    string search_string;
    string search_path;
    vector<string> filename_vec;

    AVLTree<Term> terms_tree;

    std::string persistence_filepath = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/engine_architecture/PersistenceIndex.txt";


};


#endif //INC_22S_FINAL_PROJ_INDEXHANDLER_H
