#include "../include/VariableExprNode.hpp"
#include "../include/Visitor.hpp"

void VariableExprNode::accept(Visitor &v)
{
    v.visit(this);
}
