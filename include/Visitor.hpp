#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "BinaryExprNode.hpp"
#include "DoubleNode.hpp"
#include "IntegerNode.hpp"
#include "ProgramNode.hpp"
#include "StatementNode.hpp"
#include <iostream>

class Visitor {
    public:
        virtual void visit(ProgramNode *node);
        virtual void visit(StatementNode *node);
        virtual void visit(IntegerNode *node);
        virtual void visit(DoubleNode *node);
        virtual void visit(BinaryExprNode *node);
};

#endif
