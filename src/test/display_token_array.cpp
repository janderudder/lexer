#include "TokenArray.hpp"
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
            display += std::any_cast<const char>(token.value);
        break;

        case Token::IDENTIFIER:
            display = "identifier: " + std::any_cast<std::string>(token.value);
        break;

        case Token::LIT_NUMBER:
            display = "number: " + std::to_string(std::any_cast<int>(token.value));
        break;

        case Token::LIT_STRING:
            display = "string: " + std::any_cast<std::string>(token.value);
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
