#ifndef INC_22S_FINAL_PROJ_HASHTABLE_H
#define INC_22S_FINAL_PROJ_HASHTABLE_H

#include <list>
#include <string>
#include <vector>
using namespace std;
template<typename k, typename v>
class HashTable {
public:
    HashTable ();
private:
    std::list<std::pair<std::string, std::vector<string>>> table [10000];
};


#endif //INC_22S_FINAL_PROJ_HASHTABLE_H
