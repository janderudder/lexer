/**
 *  ~~ Toy programming language ~~
 *
 *  Lexer implementation.
 *
 *  The lexer is supposed to:
 *      - Transform valid source code into a sorted array of m_tokens.
 *      - Validate source code by aborting with an error if it is invalid.
 *
 */
#include "lexer/Lexer.hpp"
#include "lexer/Token.hpp"
#include "lexer/exceptions.hpp"
#include "lexer/utils.hpp"

/**
 * Private internal methods
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
 * Error handling
 */
void Lexer::specify_valid_ids(const std::vector<Token::Id>& plop) const
{
    bool ok=false;
    for (const auto& state : plop) {
        if (m_current_token.id == state) {
            ok=true;
            break;
    }}
    if (!ok) { throw LexerSyntaxError(m_current_token, m_source_index); }
}


/**
 * Public interface
 */
TokenArray Lexer::tokenize(std::string_view source)
{
    m_source_index = 0;
    m_tokens.clear();
    begin_new_token();

    while (m_source_index != source.size())
    {
        const char c = source[m_source_index];

        switch (c)
        {
        case ' ': case '\t': case '\n': case '\0':

            if (!curr_token_is_clear())
            {
                register_current_token();
                begin_new_token();
            }

        break;


        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':

            if (curr_token_is_clear())
                begin_new_token(Token::LIT_NUMBER);

            curr_token_value_append(c);

        break;


        case '+': case '*': case '=':

            if (!curr_token_is_clear())
            {
                register_current_token();
            }

            begin_new_token(Token::BINARY_OP, c);
            register_current_token();
            begin_new_token();

        break;


        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
        case 'g': case 'h': case 'i': case 'j': case 'k': case 'l':
        case 'm': case 'n': case 'o': case 'p': case 'q': case 'r':
        case 's': case 't': case 'u': case 'v': case 'w': case 'x':
        case 'y': case 'z': case 'A': case 'B': case 'C': case 'D':
        case 'E': case 'F': case 'G': case 'H': case 'I': case 'J':
        case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
        case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V':
        case 'W': case 'X': case 'Y': case 'Z': case '_':

            if (curr_token_is_clear())
            {
                begin_new_token(Token::IDENTIFIER);
            }
            else { // error handling
                specify_valid_ids({Token::IDENTIFIER, Token::LIT_STRING});
            }

            curr_token_value_append(c);

        break;


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
        break;


        default:
        break;
        }

        ++m_source_index;

    }

    if (!curr_token_is_clear())
        register_current_token();

    return m_tokens;

}
