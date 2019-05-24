#pragma once
#include <vector>
#include "lexer/Token.hpp"

/**
 *  Lexer's output
 */
class TokenArray
{
    std::vector<Token>  m_tokens;

public:
    // Modify
    void            push(const Token&);
    void            push(Token&&);
    void            pop();
    void            clear();

    // Access
    const Token&    operator[](std::size_t) const;
    Token&          operator[](std::size_t);
    const Token&    back() const;
    Token&          back();

    // Iterate
    using iterator                  = decltype(m_tokens)::iterator;
    using const_iterator            = decltype(m_tokens)::const_iterator;
    using reverse_iterator          = decltype(m_tokens)::reverse_iterator;
    using const_reverse_iterator    = decltype(m_tokens)::const_reverse_iterator;

    iterator                        begin();
    iterator                        end();
    const_iterator                  begin()         const;
    const_iterator                  end()           const;
    const_iterator                  cbegin()        const;
    const_iterator                  cend()          const;
    reverse_iterator                rbegin();
    reverse_iterator                rend();
    const_reverse_iterator          crbegin()       const;
    const_reverse_iterator          crend()         const;

};




// Inline iteration methods
inline TokenArray::iterator TokenArray::begin()
{
    return m_tokens.begin();
}


inline TokenArray::iterator TokenArray::end()
{
    return m_tokens.end();
}


inline TokenArray::const_iterator TokenArray::begin() const
{
    return m_tokens.cbegin();
}


inline TokenArray::const_iterator TokenArray::end() const
{
    return m_tokens.cend();
}


inline TokenArray::const_iterator TokenArray::cbegin() const
{
    return m_tokens.cbegin();
}


inline TokenArray::const_iterator TokenArray::cend() const
{
    return m_tokens.cend();
}


inline TokenArray::reverse_iterator TokenArray::rbegin()
{
    return m_tokens.rbegin();
}


inline TokenArray::reverse_iterator TokenArray::rend()
{
    return m_tokens.rend();
}


inline TokenArray::const_reverse_iterator TokenArray::crbegin() const
{
    return m_tokens.crbegin();
}


inline TokenArray::const_reverse_iterator TokenArray::crend() const
{
    return m_tokens.crend();
}
