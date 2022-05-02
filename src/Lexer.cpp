#include "../include/Lexer.hpp"
#include <cstdio>

std::vector<Token> Lexer::tokenizer(std::string inText)
{
    std::vector<Token> tokens;

    TokenType tokenType { WHITESPACE };
    std::string tokenValue { "" };

    this->currentChar = inText.begin();

    while (this->currentChar != inText.end()) {
        switch (*this->currentChar) {
            case ' ':
            case '\t':
            case '\n':
            case '\r': {
                this->advance();

                break;
            }

            case '#': {
                this->makeSingleLineCommentToken(tokens, tokenType);

                break;
            }

            case '-': {
                if (*std::next(this->currentChar) == '-') {
                    this->makeMultiLineCommentToken(tokens, tokenType);
                }

                else {
                    this->makeOperatorToken(tokens, tokenType, tokenValue);
                }

                break;
            }

            case '(':
            case ')': {
                tokenValue = *this->currentChar;
                tokenType = tokenValue == "(" ? L_PAREN : R_PAREN;

                this->makeBlockToken(tokens, tokenType, tokenValue);

                break;
            }

            case '[':
            case ']': {
                tokenValue = *this->currentChar;
                tokenType = tokenValue == "[" ? L_BRACKET : R_BRACKET;

                this->makeBlockToken(tokens, tokenType, tokenValue);

                break;
            }

            case '{':
            case '}': {
                tokenValue = *this->currentChar;
                tokenType = tokenValue == "{" ? L_BRACE : R_BRACE;

                this->makeBlockToken(tokens, tokenType, tokenValue);

                break;
            }

            case ';': {
                tokenType = SEMICOLON;
                tokenValue = *this->currentChar;

                tokens.push_back(Token(tokenType, tokenValue));

                this->endToken(tokenType, tokenValue);

                this->advance();

                break;
            }

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                this->makeNumberToken(tokens, tokenType, tokenValue);

                break;
            }

            case '"': {
                this->makeStringToken(tokens, tokenType, tokenValue);

                break;
            }

            case '+':
            case '*':
            case '/': {
                this->makeOperatorToken(tokens, tokenType, tokenValue);

                break;
            }

            default: {
                tokenType = IDENTIFIER;

                while (*this->currentChar != ' ' && *this->currentChar != '(' && *this->currentChar != ')' && *this->currentChar != EOF) {
                    tokenValue.append(1, *this->currentChar);

                    this->advance();
                }

                tokens.push_back(Token(tokenType, tokenValue));

                this->endToken(tokenType, tokenValue);

                /* this->advance(); */

                break;
            }
        }
    }

    return tokens;
}

void Lexer::makeSingleLineCommentToken(std::vector<Token> &tokens, TokenType &tokenType)
{
    tokenType = COMMENT;

    while (*this->currentChar != '\n' && *this->currentChar != EOF) {
        this->advance();
    }
}

void Lexer::makeMultiLineCommentToken(std::vector<Token> &tokens, TokenType &tokenType)
{
    tokenType = COMMENT;

    bool isEndOfComment = false;

    int incrementor = 0;

    for (int i = 0; i < 3; i++) {
        this->advance();
    }

    while (*this->currentChar != EOF) {
        if (*this->currentChar == '-') {
            ++incrementor;
        }

        if (incrementor == 3) {
            break;
        }

        this->advance();
    }

    this->advance();
}

void Lexer::makeBlockToken(std::vector<Token> &tokens, TokenType &tokenType, std::string &tokenValue)
{
    tokens.push_back(Token(tokenType, tokenValue));

    this->endToken(tokenType, tokenValue);

    this->advance();
}

void Lexer::makeNumberToken(std::vector<Token> &tokens, TokenType &tokenType, std::string &tokenValue)
{
    tokenType = INTEGER_LITERAL;

    int numFloatingPoint = 0;

    while ((std::isdigit(*this->currentChar) || *this->currentChar == '.') && *this->currentChar != EOF) {
        tokenValue.append(1, *this->currentChar);

        if (numFloatingPoint > 1) {
            std::cerr << "Double literal accepts only one floating point\n";

            exit(1);
        }

        if (*this->currentChar == '.') {
            ++numFloatingPoint;

            tokenType = DOUBLE_LITERAL;
        }

        this->advance();
    }

    tokens.push_back(Token(tokenType, tokenValue));

    this->endToken(tokenType, tokenValue);
}

void Lexer::makeStringToken(std::vector<Token> &tokens, TokenType &tokenType, std::string &tokenValue)
{
    tokenType = STRING_LITERAL;

    this->advance();

    while (*this->currentChar != '"' && *this->currentChar != EOF) {
        if (*this->currentChar == '\\') {
            tokenValue.append(1, *this->currentChar);

            this->advance();
        }

        tokenValue.append(1, *this->currentChar);

        this->advance();
    }

    tokens.push_back(Token(tokenType, tokenValue));

    this->endToken(tokenType, tokenValue);

    this->advance();
}

void Lexer::makeOperatorToken(std::vector<Token> &tokens, TokenType &tokenType, std::string &tokenValue)
{
    tokenType = OPERATOR;
    tokenValue = *this->currentChar;

    tokens.push_back(Token(tokenType, tokenValue));

    this->endToken(tokenType, tokenValue);

    this->advance();
}

void Lexer::advance()
{
    std::advance(this->currentChar, 1);
}

void Lexer::endToken(TokenType &tokenType, std::string &tokenValue)
{
    tokenType = WHITESPACE;
    tokenValue.erase();
}
