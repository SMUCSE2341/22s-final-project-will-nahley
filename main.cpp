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


int main(int argc, char** argv) {

    string path = argv[2];
    string search_term = argv[1];
    Parser parse(path);
    vector<string> docs = parse.get_documents(search_term);
    for (int i = 0; i < docs.size(); i++) {
        cout << (i + 1) <<": " << docs[i] << endl;
    }



    return 0;
}
