#ifndef INC_22S_FINAL_PROJ_TERM_H
#define INC_22S_FINAL_PROJ_TERM_H

#include <vector>
#include <string>
#include <iostream>

class Term {
public:
    Term(std::string term);
    void add_document(string &current_doc_number);

    bool operator==(const Term& T);
    bool operator<(const Term& T);


    bool contains(string& docID);
    vector<string>& get_IDs();
    std::string& get_term();
    void output_IDs();

    friend ostream& operator<<(ostream& out, Term& t);

private:
    std::vector<string> documents_vector;
    std::string term;
};


#endif //INC_22S_FINAL_PROJ_TERM_H
