#include "IndexHandler.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

//Check to see if file is empty - https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c

IndexHandler::IndexHandler(string search_string, string search_path, char type) {
    this->search_string = search_string;
    this->type = type;
    Porter2Stemmer::trim(this->search_string);
    Porter2Stemmer::stem(this->search_string);
    this->search_path = search_path;
    generate_filenames();

    if (type == 't')
        persistence_filepath = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersistenceIndex.txt";
    else if(type == 'o')
        persistence_filepath = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/OrgIndex.txt";
    else if (type == 'p')
        persistence_filepath = "/mnt/c/Users/wnahl/OneDrive/Desktop/Classwork/2022 Spring/CS 2342/22s-final-project-will-nahley-2/persistence_index/PersonIndex.txt";

}


void IndexHandler::generate_filenames() {
    unique_articles = 0;
    for (const auto & entry : fs::recursive_directory_iterator(search_path)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                filename_vec.push_back(filename);
                unique_articles++; //To keep track of how many unique files there are
            }
        }
    }
}


void IndexHandler::add_terms(std::vector<std::string> &stemmed_words, std::string docID) {
    for (int i = 0; i < stemmed_words.size(); i++) { //iterating through each word and creating a Term
        Term this_term = stemmed_words[i];
        this_term.add_document(docID);

        if (type == 't') { //since the type is 't', we need to put this in the terms tree

            if (terms_tree.contains(this_term)) {
                AVLNode<Term> *node = terms_tree.find_node(this_term);
                if (!node->element.contains(docID)) { //if the tree does not contain the current docID, we add the document to the already
                    node->element.add_document(docID); //existing node
                }

            } else {
                terms_tree.insert(this_term); //If the tree does not contain the Term, we add it to tree
            }
        } else if (type == 'o') {
            if (org_tree.contains(this_term)) {
                AVLNode<Term> *node = org_tree.find_node(this_term);
                if (!node->element.contains(docID)) {
                    node->element.add_document(docID);
                }

            } else {
                org_tree.insert(this_term);
            }
        }

        else if (type == 'p') {
            if (person_tree.contains(this_term)) {
                AVLNode<Term> *node = person_tree.find_node(this_term);
                if (!node->element.contains(docID)) {
                    node->element.add_document(docID);
                }

            } else {
                person_tree.insert(this_term);
            }
        }

    }
}

void IndexHandler::populate_tree() {
    Parser p(search_path, type);

    for (int i = 0; i < filename_vec.size(); i++) {
        string cur_docID;
        vector<string> cur_text = p.get_doc_info(filename_vec[i], cur_docID);
        add_terms(cur_text, cur_docID);

    }

    //To write to the persistence index
    std::ofstream out(persistence_filepath, ios::out); //CHANGE THIS FOR TESTING
    if (!out.is_open()) {
        cout << "Not open.." << endl;
    }

    //depending on the type of IndexHandler, we print to the correct .txt file
    if (type == 't')
        terms_tree.printIO(out);
    else if (type == 'o')
        org_tree.printIO(out);
    else if (type == 'p');
    person_tree.printIO(out);

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
        //To iterate through already-existing persistence index
        // by checking if search word == current word of index
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


int IndexHandler::get_unique_articles() {
    return unique_articles;
}



