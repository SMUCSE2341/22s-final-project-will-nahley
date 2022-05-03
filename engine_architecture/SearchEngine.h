#ifndef INC_22S_FINAL_PROJ_SEARCHENGINE_H
#define INC_22S_FINAL_PROJ_SEARCHENGINE_H

#include "../data_structures/AVLTree.h"
#include "../rapidjson/document.h"
#include "../rapidjson/stringbuffer.h"
#include "Parser.h"
#include "IndexHandler.h"
#include "QueryProcessor.h"
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <chrono>

class SearchEngine {

public:
    // The search engine is the main driver of the program, with
    // only one public member function
    SearchEngine();

    void go();


private:
    static int total_num_articles();
    static int total_num_words_indexed();
    static int total_unique_orgs();
    static int total_unique_persons();


    //This search path is where all the files are located
    string search_path;


};




#endif //INC_22S_FINAL_PROJ_SEARCHENGINE_H
