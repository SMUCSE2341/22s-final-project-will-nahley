#ifndef INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJ_QUERYPROCESSOR_H

#include <vector>
#include <string>

class QueryProcessor {
public:
    QueryProcessor(std::string search_term);

    //Query parsing
    void parse_search();
    std::string& tolower(std::string& str);



private:
    std::string search_term;

    std::vector<std::string> all_words_vector;
    std::string operator_array [5] = {"and", "not", "or", "org", "person"};

    std::vector<std::string> and_vector;
    std::vector<std::string> or_vector;
    std::vector<std::string> not_vector;
    std::vector<std::string> person_vector;
    std::vector<std::string> org_vector;


};


#endif //INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
