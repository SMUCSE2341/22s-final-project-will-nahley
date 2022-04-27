#include "IndexHandler.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

//Check to see if file is empty - https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c

IndexHandler::IndexHandler(string search_string, string search_path) {
    this->search_string = search_string;
    Porter2Stemmer::trim(this->search_string);
    Porter2Stemmer::stem(this->search_string);
    this->search_path = search_path;
    generate_filenames();

    persistence_filepath = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley/persistence_index/PersistenceIndex.txt";

}


void IndexHandler::generate_filenames() {
    for (const auto & entry : fs::recursive_directory_iterator(search_path)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                filename_vec.push_back(filename);
            }
        }
    }
}

void IndexHandler::add_terms(std::vector<std::string> &stemmed_words, std::string docID) {
    for (int i = 0; i < stemmed_words.size(); i++) {
        Term this_term = stemmed_words[i];
        this_term.add_document(docID);
        if (terms_tree.contains(this_term)) {
            AVLNode<Term>* node = terms_tree.find_node(this_term);
            if (!node->element.contains(docID)) {
                node->element.add_document(docID);
            }

        } else {
            terms_tree.insert(this_term);
        }
    }
}

void IndexHandler::populate_tree() {
    Parser p(search_path);

    for (int i = 0; i < filename_vec.size(); i++) {
        string cur_docID;
        vector<string> cur_text = p.get_doc_info(filename_vec[i], cur_docID);
        add_terms(cur_text, cur_docID);

    }

    std::ofstream out(persistence_filepath, ios::out); //CHANGE THIS FOR TESTING
    if (!out.is_open()) {
        cout << "Not open.." << endl;
    }

    int i = 1;
    terms_tree.printIO(out);

}

vector<string> IndexHandler::get_correct_documents() {
    vector<string> doc_vec;

    std::ifstream in(persistence_filepath);
    if (in.peek() == std::ifstream::traits_type::eof()) { //This is the case where the persistence index is empty
        populate_tree();
        Porter2Stemmer::trim(search_string);
        Porter2Stemmer::stem(search_string);
        Term t(search_string);
        AVLNode<Term>* node = terms_tree.find_node(t);

        if (node == nullptr) {
            cout << "Could not find: " << search_string << endl;
            return doc_vec;

        }
        return node->element.get_IDs();

    } else {
        while (!in.eof()) {
            string correct = search_string + " ";
            string line;
            getline(in, line, '\n');
            if (line == "") //the bottom line of persistence index, if we hit this point we know we're at eof
                break;

            string possible = line.substr(0, correct.size());
            if (correct == possible) {
                int cursor = correct.size();
                string ID = "";
                while (cursor < line.size()) {
                    if (line[cursor] == ' ') {
                        doc_vec.push_back(ID);
                        ID = "";
                        cursor++;
                    } else {
                        ID += line[cursor];
                        cursor++;
                    }
                }
                if (ID != "")
                    doc_vec.push_back(ID);
                break;
            }
        }
        return doc_vec;
    }

}

vector<string> IndexHandler::get_org_documents() {
    return vector<string>();
}

vector<string> IndexHandler::get_person_documents() {
    return vector<string>();
}




