#include <iostream>
#include "AVLTree.h"
#include "term.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "file_cleanup/porter2_stemmer-master/porter2_stemmer.h"
#include <cassert>
#include <vector>

#include "Parser.h"
#include <fstream>

using namespace std;


int main() {
    string path = "/mnt/c/Users/wnahl/SmallJSON/";
    string search_term = "COVID";
    Parser parse(path);
    parse.print_document_data();






    return 0;
}
