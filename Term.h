#ifndef INC_22S_FINAL_PROJ_TERM_H
#define INC_22S_FINAL_PROJ_TERM_H

#include <vector>
#include <string>

class Term {
public:
    Term(std::string term);
    void add_document(int current_doc_number);

    bool operator==(const Term& T);
    bool operator<(const Term& T);

private:
    std::vector<int> documents_vector;
    std::string term;
};


#endif //INC_22S_FINAL_PROJ_TERM_H
