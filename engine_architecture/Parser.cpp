#include "Parser.h"
#include <filesystem>
#include <iostream>

// efficiently split string into words - https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
// std::binary_search - https://en.cppreference.com/w/cpp/algorithm/binary_search

using namespace std;
namespace fs = std::filesystem;

///PARSER INSTANTIATION
Parser::Parser(std::string path, char type) {
    this->path = path;
    this->type = type;
    generate_stop_words();
}

// This function pulls in the stopwords file and creates
// a vector of all the words
void Parser::generate_stop_words() {
    string p = "../file_cleanup/stop_words.txt";
    ifstream in_stream (p);
    char buff[20];
    while (in_stream.getline(buff, 635, '\n')) {
        string word = buff;
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        stop_words.push_back(word);
    }

}

/// DOCUMENT CLEANUP
// This function takes the full "text" section of JSON, then
// trims it, then pushes it into a vector where each element
// is a stem
vector<string> Parser::word_vec(string &text) {
    vector<string> word_vec;
    string word = "";
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') {
            //CHECK IF WORD IS STOP WORD?
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            if (!is_stopword(stop_words, word)) {
                if (word != "") {
                    word_vec.push_back(word);
                }
            }
            word = "";
        } else {
            word += text[i];
        }
    }
    return word_vec;
}


// Can use binary search here because the stop word list I got from
// online was already sorted
bool Parser::is_stopword(const vector<string>& vec, const string word) {

    //return false;
    return std::binary_search(vec.begin(), vec.end(), word);
}

// This function takes in the path of a file and returns the
// parsed text with stopwords removed. The id parameter is passed
// by reference so that I can also return the document's ID in
// addition to the parsed/cleaned words vector
vector<string> Parser::get_doc_info(string filepath, string& id) {

    string cur_line;
    string whole_file;
    ifstream in(filepath);
    while (getline(in, cur_line)) {
        whole_file += cur_line + '\n';
    }
    in.close();
    rapidjson::Document d;
    d.Parse(whole_file.c_str());

    id = filepath;
    //id = d["uuid"].GetString();
    string text;
    if (type == 't') { // where t represents term
        text = d["text"].GetString();
    } else if (type == 'o') {
        vector<string> organizations;
        const rapidjson::Value& orgs = d["entities"]["organizations"];
        int size = orgs.Size();
        for (int i = 0; i < size; i++) {
            organizations.push_back(orgs[i]["name"].GetString());
        }

        for (int i = 0; i < organizations.size(); i++) {
            text = text + organizations[i] + " ";
        }

    } else if (type == 'p') {
        vector<string> persons;
        const rapidjson::Value& pers = d["entities"]["persons"];
        int size = pers.Size();
        for (int i = 0; i < size; i++) {
            persons.push_back(pers[i]["name"].GetString());
        }

        for (int i = 0; i < persons.size(); i++) {
            text = text + persons[i] + " ";
        }
    }
    vector<string> clean_text = word_vec(text);
    return clean_text;

}


char Parser::get_type() {
    return type;
}











