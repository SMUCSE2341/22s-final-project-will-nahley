#ifndef INC_22S_FINAL_PROJ_PARSER_H
#define INC_22S_FINAL_PROJ_PARSER_H

#include <string>
#include <vector>
#include "AVLTree.h"
#include "Term.h"
#include <fstream>
#include "file_cleanup/porter_stemmer.cpp"

class Parser {
public:
    Parser(std::string path);
    void generate_filenames();
    void generate_stop_words();
    void clean_document(std::string path);

    void print_stop_words();

private:
    std::string path;
    std::vector<std::string> filename_vector;
    std::vector<std::string> stop_words;



    AVLTree<Term> word_tree;
    AVLTree<Term> org_tree;
    AVLTree<Term> person_tree;



};


#endif //INC_22S_FINAL_PROJ_PARSER_H
