#include "../include/BinaryExprNode.hpp"
#include "../include/Visitor.hpp"

void BinaryExprNode::accept(Visitor &v)
{
    v.visit(this);
}
