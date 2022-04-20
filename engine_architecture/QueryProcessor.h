#ifndef INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJ_QUERYPROCESSOR_H

#include <vector>
#include <string>

class QueryProcessor {
public:

    enum QUERY_TYPE {AND, OR}; //If neither is selected (1 term), then assume AND although it doesn't matter

    //Processor Initialization
    QueryProcessor(std::string search_term);
    void get_type();

    //Query parsing
    void parse_search();
    std::string& tolower(std::string& str);

    void populate_vectors();
    void populate_not(int& i);
    void populate_person(int& i);
    void populate_org(int& i);

private:
    std::string search_term;

    std::vector<std::string> all_words_vector;

    std::vector<std::string> and_vector;
    std::vector<std::string> or_vector;
    std::vector<std::string> not_vector;
    std::vector<std::string> person_vector;
    std::vector<std::string> org_vector;
    QUERY_TYPE type;


};


#endif //INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
