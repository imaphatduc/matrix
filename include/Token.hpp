#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <iostream>
#include <string>

enum TokenType {
    WHITESPACE,
    COMMENT,
    L_PAREN,
    R_PAREN,
    L_BRACKET,
    R_BRACKET,
    L_BRACE,
    R_BRACE,
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
    "L_PAREN",
    "R_PAREN",
    "L_BRACKET",
    "R_BRACKET",
    "L_BRACE",
    "R_BRACE",
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
