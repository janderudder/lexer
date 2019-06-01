/**
 *  ~~ Toy programming language ~~
 *
 *  Lexer driver program.
 *
 *  The lexer is supposed to:
 *      - Transform valid source code into a sorted array of tokens.
 *      - Validate source code by aborting with an error if it is invalid.
 *
 */
#include "lexer/Lexer.hpp"
#include "lexer/TokenArray.hpp"
#include "lexer/exceptions.hpp"
#include "test/test.hpp"
#include "timing/Chronometer.hpp"
#include "input.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

#ifndef LEXER_DRIVER_FN
#define LEXER_DRIVER_FN main
#endif


int LEXER_DRIVER_FN()
{
    const auto source = load_source_file("src/lexer/Lexer.cpp");
    Chronometer chrono;

    try
    {
        Lexer lexer;
        chrono.start();

        TokenArray tokens = lexer.tokenize(source);
        chrono.stop();

        // Show scanned tokens
        display_token_array(tokens);

        // Display time
        std::cout
            << "Tokenized in : "
            << chrono.read().as_microseconds()
            << " us\n";
    }

    catch (const LexerSyntaxError& e)
    {
        std::cout << e.what() << "\n";
    }

}
