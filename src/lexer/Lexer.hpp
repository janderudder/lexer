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
#include "char_handling/Category_Map.hpp"
#include "lexer/Token.hpp"
#include "lexer/TokenArray.hpp"
#include <string>
#include <string_view>
#include <functional>

class Lexer
{
    using char_cat_handler_t = std::function<void(const char)>;

    // Field containing char handling functions
    std::vector<char_cat_handler_t> m_char_handlers;

    // Map a char value to a Char_Category
    static Category_Map m_category_map;

    // Fields used while scanning
    TokenArray          m_tokens;
    std::size_t         m_source_index;
    Token               m_current_token;

    // Internal methods: state machine actions
    void begin_new_token(Token::Id =Token::UNASSIGNED);
    void begin_new_token(Token::Id, const char c);
    void register_current_token();
    void curr_token_value_append(const char);

    // Tests on current token state
    bool curr_token_has_value() const;
    bool curr_token_is_clear() const;
    bool curr_id_is_one_of(const std::vector<Token::Id>&) const;

    // Combination of actions.
    void register_and_begin(Token::Id =Token::UNASSIGNED);
    void register_and_begin(Token::Id, const char c);

    // Error handling
    void throw_current_state() const;

public:
    Lexer() noexcept;

    // Main public functionality
    TokenArray tokenize(std::string_view);


};
