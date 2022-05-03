#include "../include/Visitor.hpp"

void Visitor::visit(IntegerNode *node)
{
    std::cout << node->getValue() << ' ';
}
