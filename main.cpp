#include <iostream>
#include "AVLTree.h"
#include "term.h"
#include "rapidjson/document.h"
#include "Parser.h"

using namespace std;


int main() {
    string path = "/mnt/c/Users/wnahl/SmallJSON/";
    string search_term = "COVID";
    Parser parse(path);
    parse.clean_document(path);





    return 0;
}
