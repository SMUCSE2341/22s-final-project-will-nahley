#include "QueryProcessor.h"

using namespace std;

QueryProcessor::QueryProcessor(std::string search_term) {
    tolower(search_term);
    this->search_term = search_term;
    parse_search();
}

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

string& QueryProcessor::tolower(string &str) {
    for (int i = 0; i < str.size(); i++) {
        if (str[i] > 64 && str[i] < 91) {
            str[i] += 32;
        }
    }
}
