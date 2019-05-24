#pragma once
#include <stdexcept>
#include "Token.hpp"

struct LexerSyntaxError : virtual public std::runtime_error
{
    const Token         token;
    const std::size_t   source_index;

    LexerSyntaxError(Token&&, std::size_t) noexcept;
};
