#include "Parser.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

Parser::Parser(std::string path) {
    this->path = path;
}

void Parser::get_filenames() {
    for (const auto & entry : fs::recursive_directory_iterator(path)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                std::cout << filename << std::endl;
                filename_vector.push_back(filename);
            }
        }
    }
}




