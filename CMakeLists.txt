cmake_minimum_required(VERSION 3.16)
project(22s_final_proj)

set(CMAKE_CXX_STANDARD 17)

add_executable(22s_final_proj main.cpp AVLTree.h Term.cpp Term.h Parser.cpp Parser.h file_cleanup/stop_words.txt file_cleanup/porter_stemmer.cpp)
