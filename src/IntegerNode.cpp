#include "../include/IntegerNode.hpp"
#include "../include/Visitor.hpp"

void IntegerNode::accept(Visitor &v)
{
    v.visit(this);
}
