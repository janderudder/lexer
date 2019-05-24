/**
 *  ~~ Toy programming language ~~
 *
 *  Lexer header
 *
 *  The lexer is supposed to:
 *      - Transform valid source code into a sorted array of tokens.
 *      - Validate source code by aborting with an error if it is invalid.
 *
 */
#pragma once
#include "lexer/Token.hpp"
#include "lexer/TokenArray.hpp"
#include <string>
#include <string_view>

class Lexer
{
    // Fields used while scanning
    TokenArray        m_tokens;
    std::size_t       m_source_index;
    bool              m_lexing_continues;
    std::string       m_buffer;
    Token             m_current_token;

    // Internally used methods
    bool handle_buffer();

public:
    TokenArray tokenize(std::string_view);

};
