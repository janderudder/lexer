/**
 *  ~~ Toy programming language ~~
 *
 *  Lexer - input functions, implementation
 *
 *  Read Toy source code from various input
 *  sources.
 *
 */
#include "input.hpp"
#include <fstream>
#include <iostream>


std::string prompt_source()
{
    std::string source;

    std::cout <<
        "You may enter the source code here.\n"
        "A semicolon indicates the end of the string.\n\n> ";

    std::getline(std::cin, source, ';');
    return source;
}



std::string load_source_file(std::string_view path)
{
    std::string source;
    std::ifstream file {path.data()};

    if (!file) {
        std::cerr << "Error: unable to open file.\n";
    }
    else {
        // Reserve string size for performance reason
        file.seekg(0, std::ios::end);
        source.resize(file.tellg());
        file.seekg(0, std::ios::beg);

        file.read(&source[0], source.size());
        file.close();
    }
    return source;
}
