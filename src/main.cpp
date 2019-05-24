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
#include "lexer/utils.hpp"
#include "test/test.hpp"

#include <cstdio>
#include <iostream>
#include <string>

#ifndef LEXER_DRIVER_FN
#define LEXER_DRIVER_FN main
#endif


int LEXER_DRIVER_FN()
{
    std::cout <<
        "You may enter the source code here.\n"
        "A semicolon indicates the end of the string.\n\n> ";

    std::string source;
    std::getline(std::cin, source, ';');

    try
    {
        Lexer lexer;
        TokenArray tokens = lexer.tokenize(source);

        // Show scanned tokens
        display_token_array(tokens);
    }

    catch (const LexerSyntaxError& e)
    {
        std::cout << e.what() << "\n";
    }

}
