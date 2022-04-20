#include "data_structures/AVLTree.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "Parser.h"
#include "IndexHandler.h"
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>

using namespace std;

int main(int argc, char** argv) {




    IndexHandler index_handler (argv[1], argv[2]);

    vector<string> ids = index_handler.get_correct_documents();
    for (int i = 0; i < ids.size(); i++) {
        cout << (i + 1) << ": " << ids[i] << endl;
    }



    return 0;
}
