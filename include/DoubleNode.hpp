#ifndef DOUBLE_NODE_HPP
#define DOUBLE_NODE_HPP

#include "ExprNode.hpp"
#include "Token.hpp"
#include <string>

class DoubleNode : public ExprNode {
    private:
        Token token;

    public:
        DoubleNode(Token token, int line)
            : ExprNode(line)
            , token(token)
        {
        }

        int getValue()
        {
            std::string stringValue = this->token.getValue();

            double value = std::stod(stringValue);

            return value;
        }

        void accept(class Visitor &v);
};

#endif
