#include "data_structures/AVLTree.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "engine_architecture/Parser.h"
#include "engine_architecture/IndexHandler.h"
#include "engine_architecture/QueryProcessor.h"
#include <iostream>
#include <vector>
#include <functional>
#include "engine_architecture/SearchEngine.h"
#include <chrono>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    SearchEngine search;
    search.go();



    return 0;
}
