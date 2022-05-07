#include "../include/DoubleNode.hpp"
#include "../include/Visitor.hpp"

void DoubleNode::accept(Visitor &v)
{
    v.visit(this);
}
