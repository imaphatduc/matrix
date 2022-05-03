#include "../include/StatementNode.hpp"
#include "../include/Visitor.hpp"

void StatementNode::accept(Visitor &v)
{
    v.visit(this);
}
