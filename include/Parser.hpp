#ifndef PARSER_HPP
#define PARSER_HPP

#include "AstNode.hpp"
#include "BinaryExprNode.hpp"
#include "DoubleNode.hpp"
#include "ExprNode.hpp"
#include "IntegerNode.hpp"
#include "ProgramNode.hpp"
#include "StatementNode.hpp"
#include "Token.hpp"
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <stack>
#include <vector>

static std::map<char, int> BinOpPrecedence = {
    { '<', 10 },
    { '+', 20 },
    { '-', 20 },
    { '*', 40 },
    { '/', 40 },
};

class Parser {
    private:
        std::vector<Token>::iterator currentToken;

    public:
        void parse(std::vector<Token> tokens);

        std::unique_ptr<ProgramNode> parseProgramNode(std::vector<Token> tokens);
        std::unique_ptr<StatementNode> parseStatementNode();
        std::unique_ptr<ExprNode> parseExprNode();
        std::unique_ptr<ExprNode> parseLiteralNode();

        void makeBinaryExprNode(std::stack<std::unique_ptr<ExprNode>> &operandStack, std::stack<char> &operatorStack);
        std::unique_ptr<ExprNode> parseBinaryExprNode();

        int getTokPrecedence();

        void advance();
        void back();
};

#endif
