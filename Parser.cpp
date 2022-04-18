#include "Parser.h"
#include <filesystem>
#include <iostream>

// efficiently split string into words - https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/

using namespace std;
namespace fs = std::filesystem;

Parser::Parser(std::string path) {
    this->path = path;
    generate_stop_words();
    generate_filenames();
}

void Parser::generate_filenames() {
    for (const auto & entry : fs::recursive_directory_iterator(path)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                filename_vector.push_back(filename);
            }
        }
    }
}

void Parser::generate_stop_words() {
    string p = "../file_cleanup/stop_words.txt";
    ifstream in_stream (p);
    char buff[20];
    while (in_stream.getline(buff, 635, '\n')) {
        stop_words.push_back(buff);
    }

}

void Parser::clean_document(rapidjson::Document& d) {



    string t = make_lowercase(d);
    //cout << t << endl << endl << endl;
    vector<string> vec = word_vec(t);
    cout << "hello" << endl;

    /// THE PLAN
    // SEPARATE TEXT INTO A VECTOR OF WORDS
    // REMOVE ANY WORDS THAT ARE STOP WORDS (HASH TABLE?)
    // STEM ALL WORDS
    // COMBINE BACK INTO TEXT


}


string Parser::make_lowercase(rapidjson::Document& d) {
    string text = d["text"].GetString();
    for (int i = 0; i < text.size(); i++) {
        if (text[i] >= 65 && text[i] <= 90) {
            text[i] += 32;
        }
    }
    return text;
}

vector<string> Parser::word_vec(string &text) {
    vector<string> word_vec;
    string word = "";
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') {
            //CHECK IF WORD IS STOP WORD?
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            word_vec.push_back(word);
            word = "";
        } else {
            word += text[i];
        }
    }
    return word_vec;
}

void Parser::print_document_data() {

    for (int i = 0; i < filename_vector.size(); i++) {

        string cur_line;
        string whole_file;
        ifstream in(filename_vector[i]);
        while (getline(in, cur_line)) {
            whole_file += cur_line + '\n';
        }

        rapidjson::Document doc;
        doc.Parse(whole_file.c_str());


        cout << "ID: " << doc["uuid"].GetString() << endl;

        vector<string> persons;
        cout << "People: ";
        for (int i = 0 ; i < doc["entities"]["persons"].Size(); i++) {
            persons.push_back(doc["entities"]["persons"][i]["name"].GetString());
            cout << persons[i] << "  ";
        }
        cout << endl;

        vector<string> organizations;
        cout << "Organizations: ";
        for (int i = 0; i < doc["entities"]["organizations"].Size(); i++) {
            organizations.push_back(doc["entities"]["organizations"][i]["name"].GetString());
            cout << organizations[i] << "  ";
        }
        cout << endl << "Text: ";
        clean_document(doc);
    }

}







