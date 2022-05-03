#ifndef EXPR_NODE_HPP
#define EXPR_NODE_HPP

#include "AstNode.hpp"

class ExprNode : public AstNode {
    public:
        ExprNode(int line)
            : AstNode(line)
        {
        }
};

#endif
