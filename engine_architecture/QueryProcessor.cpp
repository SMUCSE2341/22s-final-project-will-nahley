#include "QueryProcessor.h"

// https://en.cppreference.com/w/cpp/algorithm/set_union
// https://en.cppreference.com/w/cpp/algorithm/set_intersection
// https://en.cppreference.com/w/cpp/algorithm/set_difference

using namespace std;

///INITIALIZING THE PROCESSOR

QueryProcessor::QueryProcessor(std::string search_term, std::string search_path) {
    this->search_term = search_term;
    this->search_path = search_path;
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

vector<string> QueryProcessor::generate_sets() {

    vector<string> total_set;

    vector<string> ao_set; //ao meaning the set that contains the results of the "AND" or "OR" clauses
    if (!and_vector.empty()) { //To handle the case where the query starts with "AND"
        IndexHandler h1(and_vector[0], search_path, 't');
        vector<string> vector1 = h1.get_correct_documents();
        std::sort(vector1.begin(), vector1.end());

        if (and_vector.size() == 1) { //one term defaults to the AND vector so this accounts for this case
            ao_set = vector1;
        } else {
            for (int i = 1; i < and_vector.size(); i++) {
                IndexHandler h2(and_vector[i], search_path, 't');
                vector<string> vector2 = h2.get_correct_documents();
                std::sort(vector2.begin(), vector2.end());
                std::set_intersection(vector1.begin(), vector1.end(), vector2.begin(), vector2.end(),
                                      std::back_inserter(ao_set));
            }
        }


    } else if (!or_vector.empty()) { //To handle the case where the query starts with "OR"
        IndexHandler h1(or_vector[0], search_path, 't');
        vector<string> vector1 = h1.get_correct_documents();
        std::sort(vector1.begin(), vector1.end());

        for (int i = 1; i < or_vector.size(); i++) {
            IndexHandler h2(or_vector[i], search_path, 't');
            vector<string> vector2 = h2.get_correct_documents();
            std::sort(vector2.begin(), vector2.end());
            std::set_union(vector1.begin(),vector1.end(), vector2.begin(), vector2.end(), std::back_inserter(ao_set));
        }
    }

    total_set = ao_set;
    return total_set;

    /*if (!person_vector.empty()) {
        vector<string> temp_set;


    }
    if (!org_vector.empty()) {
        //handle org case
    }

    if (!not_vector.empty()) {
        IndexHandler h1(not_vector[0], search_path, 't');
        vector<string> vector1 = h1.get_correct_documents(); // this vector will get the docs that we DON'T want
        std::sort(vector1.begin(), vector1.end());
        std::set_difference(ao_set.begin(), ao_set.end(), vector1.begin(), vector1.end(), std::inserter(total_set, total_set.begin()));
    }*/

}
