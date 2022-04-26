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


    AVLTree<int> tree;
    int arr [8] = {3, 1, 5, 2, 4, -3, 12, -100};
    for (int i = 0; i < 8; i++) {
        tree.insert(arr[i]);
    }


    /*std::ofstream out("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/engine_architecture/PersistenceIndex.txt", ios::app);
    if (!out.is_open()) {
        cout << "Not open.." << endl;
    }

    tree.printIO(out);
    out << endl;*/

    /*Term t ("Hello");

    string s1 = "123";
    string s2 = "234";
    string s3 = "345";


    t.add_document(s1);
    t.add_document(s2);
    t.add_document(s3);
    cout << t << endl;*/


    std::ifstream in("/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/engine_architecture/PersistenceIndex.txt", ios::app);




    string search_path = "/mnt/c/Users/wnahl/sample_data_sets/size-10";
    string search_term = "financial";
    //string search_term = "AND facebook instagram NOT tom";
    QueryProcessor query(search_term, search_path);

    IndexHandler index_handler (search_term, search_path);
    vector<string> ids = index_handler.get_correct_documents();
    for (int i = 0; i < ids.size(); i++) {
        cout << (i + 1) << ": " << ids[i] << endl;
    }



    return 0;
}
