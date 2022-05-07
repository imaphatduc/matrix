#include "../include/Parser.hpp"

void Parser::parse(std::vector<Token> tokens)
{
    this->currentToken = tokens.begin();

    this->parseProgramNode(tokens);
}

std::unique_ptr<ProgramNode> Parser::parseProgramNode(std::vector<Token> tokens)
{
    auto programNode = std::make_unique<ProgramNode>(0);

    while (this->currentToken->getType() != EOFL) {
        auto statementNode = this->parseStatementNode();

        programNode->addStatementNode(std::move(statementNode));
    }

    return programNode;
}

std::unique_ptr<StatementNode> Parser::parseStatementNode()
{
    auto exprNode = this->parseExprNode();

    if (!exprNode) {
        return nullptr;
    }

    this->advance();

    if (this->currentToken->getType() != SEMICOLON) {
        std::cerr << "Each statement must be terminated by a semicolon.\n";

        exit(1);
    }

    this->advance();

    return std::make_unique<StatementNode>(0, std::move(exprNode));
}

std::unique_ptr<ExprNode> Parser::parseExprNode()
{
    return this->parseBinaryExprNode();
}

std::unique_ptr<ExprNode> Parser::parseLiteralNode()
{
    switch (this->currentToken->getType()) {
        case INTEGER_LITERAL: {
            auto integerNode = std::make_unique<IntegerNode>(*this->currentToken, 0);

            return integerNode;
        }

        case DOUBLE_LITERAL: {
            auto doubleNode = std::make_unique<DoubleNode>(*this->currentToken, 0);

            return doubleNode;
        }

        default: {
            break;
        }
    }

    return nullptr;
}

void Parser::makeBinaryExprNode(std::stack<std::unique_ptr<ExprNode>> &operandStack, std::stack<char> &operatorStack)
{
    while (operatorStack.size() > 0) {
        auto exprNode = std::move(operandStack.top());
        operandStack.pop();

        auto rightExprNode = std::move(operandStack.top());
        operandStack.pop();

        exprNode = std::make_unique<BinaryExprNode>(operatorStack.top(), std::move(exprNode), std::move(rightExprNode), 0);

        operandStack.push(std::move(exprNode));

        operatorStack.pop();
    }
}

// Shunting yard algorithm
std::unique_ptr<ExprNode> Parser::parseBinaryExprNode()
{
    int sentinel = -10;

    std::stack<std::unique_ptr<ExprNode>> operandStack;
    std::stack<char> operatorStack;

    int lastTokPrecedence = sentinel;

    std::unique_ptr<ExprNode> exprNode = this->parseLiteralNode();

    while (true) {
        operandStack.push(std::move(exprNode));

        this->advance();

        if (!this->parseLiteralNode() && this->currentToken->getType() != OPERATOR) {

            this->makeBinaryExprNode(operandStack, operatorStack);

            exprNode = std::move(operandStack.top());

            operandStack.pop();

            lastTokPrecedence = sentinel;

            this->back();

            break;
        }

        if (this->getTokPrecedence() > lastTokPrecedence) {

            operatorStack.push(*this->currentToken->getValue().data());

            lastTokPrecedence = this->getTokPrecedence();

            this->advance();

            exprNode = this->parseLiteralNode();
        }
        else {

            this->makeBinaryExprNode(operandStack, operatorStack);

            exprNode = std::move(operandStack.top());

            operandStack.pop();

            lastTokPrecedence = sentinel;

            this->back();
        }
    }

    return exprNode;
}

int Parser::getTokPrecedence()
{
    char currentTokValue = *this->currentToken->getValue().data();

    if (!isascii(currentTokValue)) {
        return -1;
    }

    int currentTokPrecedence = BinOpPrecedence[currentTokValue];

    if (currentTokPrecedence < 0) {
        return -1;
    }

    return currentTokPrecedence;
}

void Parser::advance()
{
    std::advance(this->currentToken, 1);
}

void Parser::back()
{
    std::advance(this->currentToken, -1);
}
