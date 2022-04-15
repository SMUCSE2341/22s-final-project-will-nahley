#include "Parser.h"
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

Parser::Parser(std::string path) {
    this->path = path;
    generate_stop_words();
    generate_filenames();
}

void Parser::generate_filenames() {
    for (const auto & entry : fs::recursive_directory_iterator(path)){
        if (entry.is_regular_file()) {
            if (entry.path().extension().string() == ".json") {
                string filename = entry.path().c_str();
                filename_vector.push_back(filename);
            }
        }
    }
}

void Parser::generate_stop_words() {
    string p = "../file_cleanup/stop_words.txt";
    ifstream in_stream (p);
    char buff[20];
    while (in_stream.getline(buff, 635, '\n')) {
        stop_words.push_back(buff);
    }

}

void Parser::clean_document(std::string path) {

    /*FILE * f = fopen(path.c_str(), "r");


    stemfile(f);
    cout << "hello" << endl;*/

}







