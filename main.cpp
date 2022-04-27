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

using namespace std;

int main(int argc, char** argv) {

    /*LINUX CD PATH
    cd /mnt/c/users/wnahl/onedrive/desktop/classwork/'2022 spring'/'cs 2342'/22s-final-project-will-nahley
    */

    SearchEngine search;
    search.go();

    return 0;
}
