#ifndef INC_22S_FINAL_PROJ_PARSER_H
#define INC_22S_FINAL_PROJ_PARSER_H

#include <string>
#include <vector>
#include "AVLTree.h"
#include "Term.h"
#include <fstream>
#include "file_cleanup/porter2_stemmer-master/porter2_stemmer.h"
#include "rapidjson/document.h"
#include <unordered_map>
#include <algorithm>

class Parser {
public:
    //Creating the Parser object
    Parser(std::string path);
    void generate_filenames();
    void generate_stop_words();

    //For cleaning the documents
    void clean_document(rapidjson::Document& d);
    vector<string> word_vec(string& text);
    bool is_stopword(const vector<string>& vec, const string word);

    //To add to AVL Tree
    void insert_words(vector<string>& words, string& id);
    vector<string>& get_documents(string word);

    //For outputting data
    void print_document_data();
    void output_docIDs(std::string term);


private:
    std::string path;
    std::vector<std::string> filename_vector;
    std::vector<std::string> stop_words;



    AVLTree<Term> word_tree;
    AVLTree<Term> org_tree;
    AVLTree<Term> person_tree;



};


#endif //INC_22S_FINAL_PROJ_PARSER_H
