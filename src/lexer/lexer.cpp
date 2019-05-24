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
#include "lexer/utils.hpp"
#include <string>


TokenArray Lexer::tokenize(std::string_view source)
{
    TokenArray                  tokens;
    bool                        lexing_continues    = true;
    std::size_t                 source_index        = -1;


    while (lexing_continues)
    {
        std::string buffer;
        Token       token;

        for (source_index++; source_index < source.size(); ++source_index)
        {
            bool loop_break = false;
            const char c = source[source_index];

            switch (c)
            {
            case ' ': case '\t': case '\n':

                loop_break = true;

            break;



            case '+': case '*': case '=':

                token.id = Token::BINARY_OP;
                token.value = c;
                loop_break = true;

            break;



            case '-':

                if (!buffer.empty() && token.id != Token::LIT_STRING)
                    throw LexerSyntaxError{std::move(token), source_index};

                buffer += '-';

            break;



            case '"':

                if (buffer.empty() && token.id == Token::UNASSIGNED)
                    token.id = Token::LIT_STRING;

                else if (token.id != Token::LIT_STRING)
                    throw LexerSyntaxError{std::move(token), source_index};

            break;



            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':

                if (token.id == Token::UNASSIGNED) {
                    token.id = Token::LIT_NUMBER;
                }

                else switch (token.id) {    // Verify syntax validity
                    case Token::IDENTIFIER:
                    case Token::LIT_NUMBER:
                    case Token::LIT_STRING:
                        break;  // valid case
                    default:
                        throw LexerSyntaxError{std::move(token), source_index};
                }

                buffer += c;

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

                if (token.id == Token::LIT_NUMBER)
                    throw LexerSyntaxError{std::move(token), source_index};

                else if (token.id == Token::UNASSIGNED)
                    token.id = Token::IDENTIFIER;

                buffer += c;

            break;



            default:
            break;
            }


            if (loop_break) break;  // Escape from the inner loop

        } // inner loop end


        // Since we got out of the inner loop, perform a series of checks:
        // maybe we went over all the source...
        if (source_index == source.size())
            lexing_continues = false;

        // ...or maybe we stored some characters.
        if (!buffer.empty())
        {
            if (token.id == Token::LIT_NUMBER)
                token.value = to_number(buffer);

            else if (token.id == Token::IDENTIFIER
                    || token.id == Token::LIT_STRING)
                token.value = buffer;
        }

        // Register this token
        if (token.id != Token::UNASSIGNED)
            tokens.push(std::move(token));

    }

    return tokens;

}
