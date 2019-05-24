#pragma once
#include <any>

struct Token
{
    enum Id {   UNASSIGNED,     INVALID,
                UNARY_OP,       BINARY_OP,
                BEGIN_GROUP,    END_GROUP,
                BEGIN_BLOCK,    END_BLOCK,
                LIT_NUMBER,
                LIT_STRING,
                IDENTIFIER,
                END_INSTRUCTION,
                END_SOURCE   };

    Id          id          = UNASSIGNED;
    std::any    value;

};
