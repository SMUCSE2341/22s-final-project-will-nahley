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

    /*AVLTree<Term> tree;
    vector<string> words;
    words.push_back("hello");
    words.push_back("my");
    words.push_back("name");
    words.push_back("is");
    words.push_back("will");

    for (int i = 0; i < words.size(); i++) {
        Term current = words[i];
        tree.insert(current);
    }
    Term t("hello");
    AVLNode<Term>* node = tree.find_node(t);*/


    /*AVLTree<string> tree;
    vector<string> words;
    words.push_back("hello");
    words.push_back("my");
    words.push_back("name");
    words.push_back("is");
    words.push_back("will");

    for (int i = 0; i < words.size(); i++) {
        tree.insert(words[i]);
    }
    string text("hello");
    AVLNode<string>* ptr = tree.find_node(text);
    cout << ptr->element << endl;*/

    string path = argv[2];
    string search_term = argv[1];
    Parser parse(path);
    vector<string> docs = parse.get_documents(search_term);
    for (int i = 0; i < docs.size(); i++) {
        cout << (i + 1) <<": " << docs[i] << endl;
    }



    //parse.print_document_data();

    /*string cur_line;
    string whole_file;
    ifstream in("/mnt/c/Users/wnahl/SmallJSON/blogs_0000001.json");
    while (getline(in, cur_line)) {
        whole_file += cur_line + '\n';
    }

    rapidjson::Document doc;
    doc.Parse(whole_file.c_str());*/

    //parse.clean_document(doc);



    //parse.print_document_data();





    return 0;
}
