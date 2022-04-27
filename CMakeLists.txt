cmake_minimum_required(VERSION 3.16)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)

configure_file(file_cleanup/stop_words.txt NEWLINE_STYLE UNIX)

add_executable(22s_final_proj main.cpp data_structures/AVLTree.h Term.cpp Term.h engine_architecture/Parser.cpp engine_architecture/Parser.h file_cleanup/stop_words.txt file_cleanup/porter2_stemmer-master/porter2_stemmer.h file_cleanup/porter2_stemmer-master/porter2_stemmer.cpp file_cleanup/porter2_stemmer-master/util/hash.h file_cleanup/porter2_stemmer-master/util/string_view.h engine_architecture/IndexHandler.cpp engine_architecture/IndexHandler.h data_structures/HashTable.cpp data_structures/HashTable.h engine_architecture/QueryProcessor.cpp engine_architecture/QueryProcessor.h persistence_index/PersistenceIndex.txt engine_architecture/SearchEngine.cpp engine_architecture/SearchEngine.h)