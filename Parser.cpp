#include "Parser.h"
#include <filesystem>
#include <iostream>

// efficiently split string into words - https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/
// std::binary_search - https://en.cppreference.com/w/cpp/algorithm/binary_search
// lowercase -

using namespace std;
namespace fs = std::filesystem;

///PARSER INSTANTIATION

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

///DOCUMENT CLEANUP
// This function first stemms the entire text,
// then removes stop words,
// then adds those words to the AVL Tree
void Parser::clean_document(rapidjson::Document& d) {



    /*string t = make_lowercase(d);
    cout << t << endl << endl << endl;
    vector<string> vec = word_vec(t);*/

    string text = d["text"].GetString();
    vector<string> stemmed_words = word_vec(text);
    string id = d["uuid"].GetString();
    insert_words(stemmed_words, id);

    /// THE PLAN
    // SEPARATE TEXT INTO A VECTOR OF WORDS - DONE
    // REMOVE ANY WORDS THAT ARE STOP WORDS (HASH TABLE?)
    // STEM ALL WORDS - DONE


}

vector<string> Parser::word_vec(string &text) {
    vector<string> word_vec;
    string word = "";
    for (int i = 0; i < text.size(); i++) {
        if (text[i] == ' ') {
            //CHECK IF WORD IS STOP WORD?
            Porter2Stemmer::trim(word);
            if (!is_stopword(stop_words, word)) {
                Porter2Stemmer::stem(word);
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



bool Parser::is_stopword(const vector<string>& vec, const string word) {
    //BINARY SEARCH
    //bool is_stopword = std::binary_search(vec.begin(), vec.end(), word);

    for (int i = 0; i < stop_words.size(); i++) {
        string cur_word = stop_words[i];
        if (word + '\r' == cur_word) {
            return true;
        }
    }
    return false;

}

///ADDING TO AVL TREE

void Parser::insert_words(vector<string>& words, string& id) {

    for (int i = 0; i < words.size(); i++) {
        Term this_term = words[i];
        this_term.add_document(id);
        if (word_tree.contains(this_term)) {
            AVLNode<Term>* node = word_tree.find_node(this_term);
            if (!node->element.contains(id)) {
                node->element.add_document(id);
            }

        } else {
            word_tree.insert(this_term);
        }
    }

}

vector<string> Parser::get_documents(string word) {

    //To clean docs and add to AVL
    for (int i = 0; i < filename_vector.size(); i++) {
        string cur_line;
        string whole_file;
        ifstream in(filename_vector[i]);
        while (getline(in, cur_line)) {
            whole_file += cur_line + '\n';
        }

        rapidjson::Document doc;
        doc.Parse(whole_file.c_str());
        clean_document(doc);
    }


    vector<string> doc_vec;

    Porter2Stemmer::trim(word);
    Porter2Stemmer::stem(word);
    Term t(word);
    AVLNode<Term>* node = word_tree.find_node(t);
    if (node == nullptr) {
        cout << "Could not find: " << word << endl;
        return doc_vec;

    }
    doc_vec = node->element.get_IDs();
    return doc_vec;
}

///OUTPUTTING DATA

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






