#ifndef _LEXER_HPP_
#define _LEXER_HPP_

#include "Token.hpp"

#include <iostream>
#include <iterator>
#include <locale>
#include <vector>

class Lexer {
    private:
        std::string::iterator currentChar;

        void makeSingleLineCommentToken(std::vector<Token> &tokens, TokenType &tokenType);
        void makeMultiLineCommentToken(std::vector<Token> &tokens, TokenType &tokenType);
        void makeNumberToken(std::vector<Token> &tokens, TokenType &tokenType, std::string &tokenValue);
        void makeStringToken(std::vector<Token> &tokens, TokenType &tokenType, std::string &tokenValue);
        void makeOperatorToken(std::vector<Token> &tokens, TokenType &tokenType, std::string &tokenValue);

        void advance();

        void endToken(TokenType &tokenType, std::string &tokenValue);

    public:
        std::vector<Token> tokenizer(std::string inText);
};

#endif
