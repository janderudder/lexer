#include "lexer/TokenArray.hpp"


void TokenArray::push(const Token& token)
{
    m_tokens.push_back(token);
}



void TokenArray::push(Token&& token)
{
    m_tokens.emplace_back(std::move(token));
}



void TokenArray::pop()
{
    m_tokens.pop_back();
}



const Token& TokenArray::operator[](std::size_t idx) const
{
    return m_tokens[idx];
}



Token& TokenArray::operator[](std::size_t idx)
{
    return m_tokens[idx];
}



const Token& TokenArray::back() const
{
    return m_tokens.back();
}



Token& TokenArray::back()
{
    return m_tokens.back();
}
