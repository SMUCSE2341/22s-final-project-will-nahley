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

    string cur_line;
    string whole_file;
    ifstream in("/mnt/c/Users/wnahl/SmallJSON/blogs_0000001.json");
    while (getline(in, cur_line)) {
        whole_file += cur_line + '\n';
    }

    rapidjson::Document doc;
    doc.Parse(whole_file.c_str());

    parse.clean_document(doc);


    //parse.print_document_data();





    return 0;
}
