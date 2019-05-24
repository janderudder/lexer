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
 * Private internal method
 */
bool Lexer::handle_buffer()
{
    if (!m_buffer.empty())
    {
        if (m_current_token.id == Token::LIT_NUMBER)
            m_current_token.value = to_number(m_buffer);

        else if (m_current_token.id == Token::IDENTIFIER
                || m_current_token.id == Token::LIT_STRING)
            m_current_token.value = m_buffer;

        return true;
    }
    return false;
}


/**
 * Public interface
 */
TokenArray Lexer::tokenize(std::string_view source)
{
    // (re)init. fields
    m_tokens.clear();
    m_lexing_continues    = true;
    m_source_index        = -1;


    while (m_lexing_continues)
    {
        m_buffer.clear();
        m_current_token.id = Token::UNASSIGNED;
        m_current_token.value.reset();

        for (m_source_index++; m_source_index < source.size(); ++m_source_index)
        {
            bool loop_break = false;
            const char c = source[m_source_index];

            switch (c)
            {
            case ' ': case '\t': case '\n':

                loop_break = true;

            break;



            case '+': case '*': case '=':

                if (m_current_token.id != Token::UNASSIGNED) {
                    if (handle_buffer())
                        m_tokens.push(m_current_token);
                }

                m_current_token.id = Token::BINARY_OP;
                m_current_token.value = c;
                loop_break = true;

            break;



            case '-':

                if (!m_buffer.empty() && m_current_token.id != Token::LIT_STRING)
                    throw LexerSyntaxError{std::move(m_current_token), m_source_index};

                m_buffer += '-';

            break;



            case '"':

                if (m_buffer.empty() && m_current_token.id == Token::UNASSIGNED)
                    m_current_token.id = Token::LIT_STRING;

                else if (m_current_token.id != Token::LIT_STRING)
                    throw LexerSyntaxError{std::move(m_current_token), m_source_index};

            break;



            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':

                if (m_current_token.id == Token::UNASSIGNED) {
                    m_current_token.id = Token::LIT_NUMBER;
                }

                else switch (m_current_token.id) {    // Verify syntax validity
                    case Token::IDENTIFIER:
                    case Token::LIT_NUMBER:
                    case Token::LIT_STRING:
                        break;  // valid case
                    default:
                        throw LexerSyntaxError{std::move(m_current_token), m_source_index};
                }

                m_buffer += c;

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

                if (m_current_token.id == Token::LIT_NUMBER)
                    throw LexerSyntaxError{std::move(m_current_token), m_source_index};

                else if (m_current_token.id == Token::UNASSIGNED)
                    m_current_token.id = Token::IDENTIFIER;

                m_buffer += c;

            break;



            default:
            break;
            }


            if (loop_break) break;  // Escape from the inner loop

        } // inner loop end


        // Since we got out of the inner loop, perform a series of checks:
        // maybe we went over all the source...
        if (m_source_index == source.size())
            m_lexing_continues = false;

        // ...or maybe we stored some characters.
        handle_buffer();

        // Register the current token
        if (m_current_token.id != Token::UNASSIGNED)
            m_tokens.push(m_current_token);

    }

    return m_tokens;

}
