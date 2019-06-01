/**
 *  ~~ Toy programming language ~~
 *
 *  Lexer implementation.
 *
 *  The lexer is supposed to:
 *      - Transform valid source code into a sorted array of tokens.
 *      - Validate source code by aborting with an error if it is invalid.
 *
 */
#include "lexer/Lexer.hpp"
#include "lexer/Token.hpp"
#include "lexer/exceptions.hpp"

/**
 *  Static member
 */
Category_Map Lexer::m_category_map;


/**
 *  Private internal methods
 */
void Lexer::begin_new_token(Token::Id id)
{
    m_current_token.id = id;
    m_current_token.value.clear();
}



void Lexer::begin_new_token(Token::Id id, const char begin_content)
{
    m_current_token.id = id;
    m_current_token.value = begin_content;
}



void Lexer::register_current_token()
{
    m_tokens.push(m_current_token);
}



bool Lexer::curr_token_has_value() const
{
    return !m_current_token.value.empty();
}



bool Lexer::curr_token_is_clear() const
{
    return m_current_token.id == Token::UNASSIGNED
        && m_current_token.value.empty();
}



bool Lexer::curr_id_is_one_of(const std::vector<Token::Id>& ids_array) const
{
    for (const auto id : ids_array) {
        if (m_current_token.id == id)
            return true;
    }
    return false;
}



void Lexer::curr_token_value_append(const char c)
{
    m_current_token.value += c;
}



void Lexer::register_and_begin(Token::Id id)
{
    if (m_current_token.id != Token::UNASSIGNED)
        m_tokens.push(m_current_token);

    m_current_token.id = id;
    m_current_token.value.clear();
}



void Lexer::register_and_begin(Token::Id id, const char begin_content)
{
    if (m_current_token.id != Token::UNASSIGNED)
        m_tokens.push(m_current_token);

    m_current_token.id = id;
    m_current_token.value = begin_content;
}


/**
 *  Error handling
 */
void Lexer::throw_current_state() const
{
    throw LexerSyntaxError{m_current_token, m_source_index};
}


/**
 *  Public interface
 */
Lexer::Lexer() noexcept
    : m_char_handlers(Char_Category::CAT_COUNT)
{
    if (!Category_Map::is_init())
        Category_Map::init();

    // Initialize character categories handlers array
    m_char_handlers[Char_Category::ALPHABETIC] = [this](const char c)
    {
        if (curr_token_is_clear()) {
            begin_new_token(Token::IDENTIFIER);
        }

        else if (!curr_id_is_one_of({Token::IDENTIFIER, Token::LIT_STRING})) {
            throw_current_state();
        }

        curr_token_value_append(c);
    };


    m_char_handlers[Char_Category::NUMERIC] = [this](const char c)
    {
        if (curr_token_is_clear())
            begin_new_token(Token::LIT_NUMBER);

        curr_token_value_append(c);
    };


    m_char_handlers[Char_Category::OPERATOR] = [this](const char c)
    {
        if (!curr_token_is_clear())
        {
            register_current_token();
        }

        begin_new_token(Token::BINARY_OP, c);
        register_and_begin();
    };


    m_char_handlers[Char_Category::PUNCTUATION] = [this](const char)
    {

    };


    m_char_handlers[Char_Category::DELIMITER] = [this](const char)
    {
        if (!curr_token_is_clear())
        {
            register_and_begin();
        }
    };


    m_char_handlers[Char_Category::END_OF_FILE] = [this](const char)
    {
        register_and_begin(Token::END_SOURCE);
        register_and_begin();
    };


    m_char_handlers[Char_Category::OTHER] = [this](const char c)
    {
        switch (c)
        {
        case '(':
            register_and_begin(Token::BEGIN_GROUP);
            register_and_begin();
        break;

        case ')':
            register_and_begin(Token::END_GROUP);
            register_and_begin();
        break;

        case '{':
            register_and_begin(Token::BEGIN_BLOCK);
            register_and_begin();
        break;

        case '}':
            register_and_begin(Token::END_BLOCK);
            register_and_begin();
        default:
        break;
        }
    };

}



TokenArray Lexer::tokenize(std::string_view source)
{
    m_source_index = 0;
    m_tokens.clear();
    begin_new_token();

    while (m_source_index != source.size())
    {
        const char c = source[m_source_index];

        std::invoke(m_char_handlers[m_category_map.category_of(c)], c);

        ++m_source_index;
    }

    if (!curr_token_is_clear())
        register_current_token();

    return m_tokens;

}
