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
    Token             m_current_token;

    // Internally used methods
    void begin_new_token(Token::Id =Token::UNASSIGNED);
    void begin_new_token(Token::Id, const char c);
    void register_current_token();
    void curr_token_value_append(const char);

    // Nicer spelling conditions
    bool curr_token_has_value() const;
    bool curr_token_is_clear() const;

    // Combination of previous two categories
    // of methods
    void register_and_begin(Token::Id =Token::UNASSIGNED);
    void register_and_begin(Token::Id, const char c);

    // Error handling
    void specify_valid_ids(const std::vector<Token::Id>& plop) const;

public:
    // Main public functionality
    TokenArray tokenize(std::string_view);


};
