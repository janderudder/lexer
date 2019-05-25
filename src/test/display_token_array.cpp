#include "lexer/TokenArray.hpp"
#include <iostream>
#include <string>


void display_token_array(const TokenArray& tokens)
{
    for (const auto& token : tokens) {
        std::string display;

        switch (token.id)
        {
        case Token::BINARY_OP:
            display = "binary operation: ";
            display += token.value;
        break;

        case Token::IDENTIFIER:
            display = "identifier: " + token.value;
        break;

        case Token::LIT_NUMBER:
            display = "number: " + token.value;
        break;

        case Token::LIT_STRING:
            display = "string: " + token.value;
        break;

        case Token::BEGIN_GROUP:
            display = "left_paren(";
        break;

        case Token::END_GROUP:
            display = ")right_paren:";
        break;

        case Token::BEGIN_BLOCK:
            display = "left_brace{";
        break;

        case Token::END_BLOCK:
            display = "}right_brace:";
        break;

        case Token::UNASSIGNED:
            display = "UNASSIGNED";
        break;

        default:
            display = "INVALID";
        break;
        }

        std::cout << display << "\n";

    }
}
