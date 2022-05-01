#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_

#include <iostream>
#include <string>

enum TokenType {
    WHITESPACE,
    COMMENT,
    SEMICOLON,
    IDENTIFIER,
    KEYWORD,
    OPERATOR,
    INTEGER_LITERAL,
    DOUBLE_LITERAL,
    STRING_LITERAL,
    STRING_ESCAPE_SEQUENCE,
};

static const std::string sTokenType[] {
    "WHITESPACE",
    "COMMENT",
    "SEMICOLON",
    "IDENTIFIER",
    "KEYWORD",
    "OPERATOR",
    "INTEGER_LITERAL",
    "DOUBLE_LITERAL",
    "STRING_LITERAL",
    "STRING_ESCAPE_SEQUENCE",
};

class Token {
    private:
        TokenType type;
        std::string value;

    public:
        Token(TokenType type, std::string value)
            : type(type)
            , value(value)
        {
        }

        void debugLog();
};

#endif
