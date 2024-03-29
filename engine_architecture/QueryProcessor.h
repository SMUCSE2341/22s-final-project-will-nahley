#ifndef INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJ_QUERYPROCESSOR_H

#include <vector>
#include <string>
#include <set>
#include "IndexHandler.h"
#include "../DSDoc.h"

class QueryProcessor {
public:

    enum QUERY_TYPE {AND, OR, NEITHER};

    //Processor Initialization
    QueryProcessor(std::string search_term, std::string search_path);
    void get_type();

    //Query parsing
    void parse_search();

    void populate_vectors();
    void populate_not(int& i);
    void populate_person(int& i);
    void populate_org(int& i);

    //Configure Sets
    vector<string> generate_and_or_set();
    vector<string> generate_full_set();


    //Sort documents by relevancy
    vector<DSDoc> generate_sorted_set();

private:
    std::string search_term;
    std::string search_path;

    std::vector<std::string> all_words_vector;

    std::vector<std::string> and_vector;
    std::vector<std::string> or_vector;
    std::vector<std::string> not_vector;
    std::vector<std::string> person_vector;
    std::vector<std::string> org_vector;

    std::vector<std::string> sorted_docs;


    QUERY_TYPE type;


};


#endif //INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
