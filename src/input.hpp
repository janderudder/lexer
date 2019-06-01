/**
 *  ~~ Toy programming language ~~
 *
 *  Lexer - input functions, header
 *
 *  Read Toy source code from various input
 *  sources.
 *
 */
#include "lexer/Lexer.hpp"
#pragma once
#include <string>
#include <string_view>

// Read from stdin after prompting user
std::string prompt_source();

// Read from a file
std::string load_source_file(std::string_view);
