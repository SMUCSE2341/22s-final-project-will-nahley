#ifndef INC_22S_FINAL_PROJ_PARSER_H
#define INC_22S_FINAL_PROJ_PARSER_H
#include <string>
#include <vector>
#include "../data_structures/AVLTree.h"
#include "../Term.h"
#include <fstream>
#include "../file_cleanup/porter2_stemmer-master/porter2_stemmer.h"
#include "../rapidjson/document.h"
#include <unordered_map>
#include <algorithm>
#include <chrono>

class Parser {
public:

//    C:\Users\wnahl\OneDrive\Desktop\Classwork\2022 Spring\CS 2342\22s-final-project-will-nahley

    //Creating the Parser object
    Parser(std::string path, char type);
    void generate_stop_words();

    //For cleaning the documents
    vector<string> word_vec(string& text);
    bool is_stopword(const vector<string>& vec, const string word);

    //To be passed to handler to add to AVL tree
    vector<string> get_doc_info (string filepath, string& id);

    //To get the type
    char get_type();


private:
    std::string path;
    char type;
    std::vector<std::string> stop_words;
};


#endif //INC_22S_FINAL_PROJ_PARSER_H
