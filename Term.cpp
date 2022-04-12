

using namespace std;

#include "Term.h"

Term::Term(std::string term) {
    this->term = term;
}

void Term::add_document(int current_doc_number) {
    documents_vector.push_back(current_doc_number);
}

bool Term::operator==(const Term &T) {
    return (term == T.term);
}

bool Term::operator<(const Term &T) {
    return (term < T.term);
}




