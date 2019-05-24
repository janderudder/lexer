#include "exceptions.hpp"
#include <string>


LexerSyntaxError::LexerSyntaxError(Token&& tok, std::size_t idx) noexcept
    : std::runtime_error{"syntax error."}
    , token             {std::move(tok)}
    , source_index      {idx}
{
}
