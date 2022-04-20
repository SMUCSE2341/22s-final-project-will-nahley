#include "data_structures/AVLTree.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "engine_architecture/Parser.h"
#include "engine_architecture/IndexHandler.h"
#include "engine_architecture/QueryProcessor.h"
#include <iostream>
#include <vector>
#include <functional>
#include <chrono>

using namespace std;

int main(int argc, char** argv) {

    string search_path = "/mnt/c/Users/wnahl/sample_data_sets/size-221";
    string search_term = "OR facebook instagram NOT bankruptcy ORG snap PERSON cramer";

    QueryProcessor query(search_term);
    cout << "Hello" << endl;

    /*std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();

    IndexHandler index_handler (search_term, search_path);
    vector<string> ids = index_handler.get_correct_documents();
    for (int i = 0; i < ids.size(); i++) {
        cout << (i + 1) << ": " << ids[i] << endl;
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> t = end - start;
    cout << std::fixed << t.count() << std::endl;*/

    return 0;
}
