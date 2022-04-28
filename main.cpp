#include "data_structures/AVLTree.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "engine_architecture/Parser.h"
#include "engine_architecture/IndexHandler.h"
#include "engine_architecture/QueryProcessor.h"
#include <iostream>
#include <vector>
#include <functional>
#include "engine_architecture/SearchEngine.h"
#include <chrono>

using namespace std;

int main(int argc, char** argv) {

    /*LINUX CD PATH
    cd /mnt/c/users/wnahl/onedrive/desktop/classwork/'2022 spring'/'cs 2342'/22s-final-project-will-nahley
    */

    /*SearchEngine search;
    search.go();*/

    string path = "/mnt/c/Users/wnahl/sample_data_sets/size-221";
    IndexHandler handler("cole", path, 'p');
    vector<string> ids = handler.get_correct_documents();
    for (int i = 0; i < ids.size(); i++) {
        cout << (i + 1) <<": " << ids[i] << endl;
    }

    return 0;
}
