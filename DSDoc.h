#ifndef INC_22S_FINAL_PROJ_DSDOC_H
#define INC_22S_FINAL_PROJ_DSDOC_H

#include <string>
#include <vector>
#include <fstream>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"

class DSDoc {
public:
    DSDoc(std::string filepath, std::vector<std::string> terms);

    DSDoc(const DSDoc& other);
    DSDoc& operator= (const DSDoc& other);

    std::string get_title();
    std::string get_text();
    std::string get_publication();
    std::string get_url();
    std::string get_date_published();
    double get_relevancy();

    bool operator<(const DSDoc& other) const;

private:
    std::string filepath;
    std::vector<std::string> terms;
    rapidjson::Document doc;
    double relevancy;
};


#endif //INC_22S_FINAL_PROJ_DSDOC_H
