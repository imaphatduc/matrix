#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "IntegerNode.hpp"
#include <iostream>

class Visitor {
    public:
        virtual void visit(IntegerNode *node);
};

#endif
