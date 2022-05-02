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
    } else {
        type = NEITHER;
    }


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
    } else if (type == OR) {
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
    } else {
        for (int i = 0; i < all_words_vector.size(); i++) {
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

vector<string> QueryProcessor::generate_and_or_set() {

    // Depending on the input, we can have a scenario with either AND, OR, or a single term
    // For simplicity, I will assume that a single term will be placed in the AND vector

    if (!and_vector.empty()) { //To handle the case where the query starts with "AND"
        IndexHandler first_handler(and_vector[0], search_path, 't');
        vector<string> intersection = first_handler.get_correct_documents();
        std::sort(intersection.begin(), intersection.end());


        if (and_vector.size() == 1) { //one term defaults to the AND vector so we just return the first vector
            return intersection;

        } else {
            for (int i = 1; i < and_vector.size(); i++) {
                // Using a loop here because we have to assume that there could be more than one
                // AND term, so by creating a vector for each, we can get one combined set
                vector<string> vec = intersection;
                intersection.clear();
                IndexHandler current_handler(and_vector[i], search_path, 't');
                vector<string> current_vector = current_handler.get_correct_documents();
                std::sort(current_vector.begin(), current_vector.end());
                std::sort(vec.begin(), vec.end());
                std::set_intersection(vec.begin(), vec.end(), current_vector.begin(), current_vector.end(),std::back_inserter(intersection));
            }

            return intersection;
        }


    } else if (!or_vector.empty()) { //To handle the case where the query starts with "OR"
        IndexHandler first_handler(or_vector[0], search_path, 't');
        vector<string> union_vec = first_handler.get_correct_documents();
        std::sort(union_vec.begin(), union_vec.end());

            for (int i = 1; i < or_vector.size(); i++) {
                // Using a loop here because we have to assume that there could be more than one
                // AND term, so by creating a vector for each, we can get one combined set
                vector<string> vec = union_vec;
                union_vec.clear();
                IndexHandler current_handler(or_vector[i], search_path, 't');
                vector<string> current_vector = current_handler.get_correct_documents();
                std::sort(current_vector.begin(), current_vector.end());
                std::sort(vec.begin(), vec.end());
                std::set_union(vec.begin(), vec.end(), current_vector.begin(), current_vector.end(),std::back_inserter(union_vec));
            }

            return union_vec;

    }

    vector<string> empty_set;
    return empty_set;


}

vector<string> QueryProcessor::generate_full_set() {
    vector<string> full_set = generate_and_or_set();

    if (!person_vector.empty()) {
        vector<string> temp_set = full_set;
        full_set.clear(); //clearing the full set, so it can be the destination for our set_intersection
        IndexHandler p_handler(person_vector[0], search_path, 'p');
        vector<string> person_set = p_handler.get_correct_documents(); //person_set represents all the documents where a given person appears
        std::sort(temp_set.begin(), temp_set.end());
        std::sort(person_set.begin(), person_set.end());
        if (!temp_set.empty()) //if the temp_set (full_set) is empty, we don't want to set an intersection because then it won't return anything
            std::set_intersection(temp_set.begin(), temp_set.end(), person_set.begin(), person_set.end(), std::back_inserter(full_set)); //temp set represents the docs we already have
        else                                                                                                                                //and we combine that with person set for the correct total set
            full_set = person_set;
    }

    if (!org_vector.empty()) { //repeating with orgs
        vector<string> temp_set = full_set;
        full_set.clear();
        IndexHandler o_handler(org_vector[0], search_path, 'o');
        vector<string> org_set = o_handler.get_correct_documents();
        std::sort(temp_set.begin(), temp_set.end());
        std::sort(org_set.begin(), org_set.end());
        if (!temp_set.empty())
            std::set_intersection(temp_set.begin(), temp_set.end(), org_set.begin(), org_set.end(), std::back_inserter(full_set)); //temp set represents the docs we already have
        else                                                                                                                                //and we combine that with person set for the correct total set
            full_set = org_set;
    }

    if (!not_vector.empty()) {
        vector<string> temp_set = full_set;
        full_set.clear();
        IndexHandler n_handler(not_vector[0], search_path, 't'); //using type 't' here because NOT refers to terms
        vector<string> not_set = n_handler.get_correct_documents();
        std::sort(temp_set.begin(), temp_set.end());
        std::sort(not_set.begin(), not_set.end());
        std::set_difference(temp_set.begin(), temp_set.end(), not_set.begin(), not_set.end(), std::back_inserter(full_set)); //Don't need to use if statement here because if
    }                                                                                                                           //full_set is empty, we won't want to return anything

    return full_set;

}

void QueryProcessor::clear_index() {

    IndexHandler h("NA", search_path, 't');
    h.clear();
}

