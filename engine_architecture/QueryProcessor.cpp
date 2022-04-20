#include "QueryProcessor.h"

using namespace std;

///INITIALIZING THE PROCESSOR

QueryProcessor::QueryProcessor(std::string search_term) {
    this->search_term = search_term;
    parse_search();
    get_type();
    populate_vectors();
}

void QueryProcessor::get_type() {
    if (all_words_vector[0] == "AND") {
        type = AND;
        return;
    } else if (all_words_vector[0] == "OR") {
        type = OR;
        return;
    }
    type = AND;
    and_vector.push_back(all_words_vector[0]);

}

///PARSING THE QUERY

void QueryProcessor::parse_search() {

    string word = "";
    for (int i = 0; i < search_term.size()+ 1; i++) {

        if ((search_term[i] == ' ' && word != "") || (i == search_term.size())) {
            all_words_vector.push_back(word); // If the current char is a space, we know we're
            word = "";                        // at the end of a word, or if we're at the end
        } else {                              // of the string, it must be the end of the word
            word += search_term[i];
        }

    }
}

void QueryProcessor::populate_vectors() {

    if (type == AND) {
        for (int i = 1; i < all_words_vector.size(); i++) { //Starting at 1 because the first term is AND
            string current_word = all_words_vector[i];
            if (current_word == "NOT") {
                populate_not(i);
            } else if (current_word == "PERSON") {
                populate_person(i);
            } else if (current_word == "ORG") {
                populate_org(i);
            } else {
                and_vector.push_back(current_word);
            }
        }
    } else {
        for (int i = 1; i < all_words_vector.size(); i++) { //Starting at 1 because the first term is OR
            string current_word = all_words_vector[i];
            if (current_word == "NOT") {
                populate_not(i);
            } else if (current_word == "PERSON") {
                populate_person(i);
            } else if (current_word == "ORG") {
                populate_org(i);
            } else {
                or_vector.push_back(current_word);
            }
        }
    }

}

void QueryProcessor::populate_not(int& i) {
    i++;
    while (i < all_words_vector.size()) {
        string current_word = all_words_vector[i];
        if (all_words_vector[i] == "PERSON") {
            return;
        } else if (all_words_vector[i] == "ORG") {
            return;
        } else {
            not_vector.push_back(current_word);
            return;
        }
    }
}

void QueryProcessor::populate_person(int &i) {
    i++;
    while (i < all_words_vector.size()) {
        string current_word = all_words_vector[i];
        if (all_words_vector[i] == "ORG") {
            return;
        } else {
            person_vector.push_back(current_word);
            return;
        }
    }
}

void QueryProcessor::populate_org(int &i) {
    i++;
    while (i < all_words_vector.size()) {
        string current_word = all_words_vector[i];
        if (all_words_vector[i] == "PERSON") {
            return;
        } else {
            org_vector.push_back(current_word);
            return;
        }
    }
}
