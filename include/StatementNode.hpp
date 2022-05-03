#ifndef STATEMENT_NODE_HPP
#define STATEMENT_NODE_HPP

#include "AstNode.hpp"
#include "ExprNode.hpp"
#include <memory>

class StatementNode : public AstNode {
    private:
        std::unique_ptr<ExprNode> exprNode;

    public:
        StatementNode(int line, std::unique_ptr<ExprNode> exprNode)
            : AstNode(line)
            , exprNode(std::move(exprNode))
        {
        }

        std::unique_ptr<ExprNode> getExprNode()
        {
            return std::move(this->exprNode);
        }

        void accept(class Visitor &v);
};

#endif
