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
    parse.clean_document(path);

    char * loc = "/mnt/c/Users/wnahl/SmallJSON/blogs_0000001.json";



    ifstream in(loc);
    string cur_line;
    string whole_file;

    while (getline(in, cur_line)) {
        whole_file += cur_line + '\n';
    }
    //const char* data = whole_file.c_str();

    rapidjson::Document doc;
    doc.Parse(whole_file.c_str());
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    //cout << buffer.GetString() << endl;
    //rapidjson::Value& val = doc["entities"];
    assert(doc.HasMember("entities"));
    assert(doc["entities"].HasMember("organizations"));


    vector<string> persons;
    for (int i = 0 ; i < doc["entities"]["persons"].Size(); i++) {
        persons.push_back(doc["entities"]["persons"][i]["name"].GetString());
    }

    for (int i = 0; i < persons.size(); i++) {
        cout << persons[i] << endl;
    }







    return 0;
}
