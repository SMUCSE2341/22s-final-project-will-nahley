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

class SearchEngine {

public:
    SearchEngine();

    void go();

private:
    string search_path;

};




#endif //INC_22S_FINAL_PROJ_SEARCHENGINE_H
