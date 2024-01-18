#include "../include/Visitor.hpp"

void Visitor::visit(ProgramNode *node)
{
}

void Visitor::visit(StatementNode *node)
{
}

void Visitor::visit(IntegerNode *node)
{
    std::cout << node->getValue() << ' ';
}

void Visitor::visit(DoubleNode *node)
{
    std::cout << node->getValue() << ' ';
}

void Visitor::visit(BinaryExprNode *node)
{
}

void Visitor::visit(VariableExprNode *node)
{
}
