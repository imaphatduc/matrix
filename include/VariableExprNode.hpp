#ifndef VARIABLE_EXPR_NODE_HPP
#define VARIABLE_EXPR_NODE_HPP

#include "ExprNode.hpp"
#include <string>

class VariableExprNode : public ExprNode {
    private:
        std::string name;

    public:
        VariableExprNode(std::string name, int line)
            : ExprNode(line)
            , name(name)
        {
        }

        std::string getName()
        {
            return this->name;
        }

        void accept(class Visitor &v);
};

#endif
