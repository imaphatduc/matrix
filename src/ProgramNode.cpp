#include "../include/ProgramNode.hpp"
#include "../include/Visitor.hpp"

void ProgramNode::addStatementNode(std::unique_ptr<StatementNode> statementNode)
{
    this->statementNodes.push_back(std::move(statementNode));
}

void ProgramNode::accept(Visitor &v)
{
    v.visit(this);
}
