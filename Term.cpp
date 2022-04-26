

using namespace std;

#include "Term.h"

Term::Term(std::string term) {
    this->term = term;
}

void Term::add_document(string &current_doc_number) {
    documents_vector.push_back(current_doc_number);
}

bool Term::operator==(const Term &T) {
    return (term == T.term);
}

bool Term::operator<(const Term &T) {
    return (term < T.term);
}

bool Term::contains(string& docID) {
    for (int i = 0; i < documents_vector.size(); i++) {
        if (docID == documents_vector[i]) {
            return true;
        }
    }
    return false;
}

vector<string>& Term::get_IDs() {
    return documents_vector;
}

std::string& Term::get_term() {
    return term;
}

void Term::output_IDs() {
    for (int i = 0; i < documents_vector.size(); i++) {
        std::cout << documents_vector[i] << std::endl;
    }
}

ostream& operator<<(ostream& out, Term& t) {
    out << t.get_term() << " ";
    for (int i = 0; i < t.get_IDs().size() - 1; i++) {
        out << t.get_IDs()[i] << " ";
    }
    out << t.get_IDs()[t.get_IDs().size() - 1];

}




