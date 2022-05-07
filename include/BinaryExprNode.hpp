#ifndef BINARY_EXPR_NODE_HPP
#define BINARY_EXPR_NODE_HPP

#include "ExprNode.hpp"
#include <memory>

class BinaryExprNode : public ExprNode {
    private:
        char binOp;

        std::unique_ptr<ExprNode> leftExprNode, rightExprNode;

    public:
        BinaryExprNode(char binOp, std::unique_ptr<ExprNode> leftExprNode, std::unique_ptr<ExprNode> rightExprNode, int line)
            : ExprNode(line)
            , binOp(binOp)
            , leftExprNode(std::move(leftExprNode))
            , rightExprNode(std::move(rightExprNode))
        {
        }

        char getBinOp()
        {
            return this->binOp;
        }

        std::unique_ptr<ExprNode> getLeftExprNode()
        {
            return std::move(this->leftExprNode);
        }

        std::unique_ptr<ExprNode> getRightExprNode()
        {
            return std::move(this->rightExprNode);
        }

        void accept(class Visitor &v);
};

#endif
