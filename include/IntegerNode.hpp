#ifndef INTEGER_NODE_HPP
#define INTEGER_NODE_HPP

#include "ExprNode.hpp"
#include "Token.hpp"
#include <string>

class IntegerNode : public ExprNode {
    private:
        Token token;

    public:
        IntegerNode(Token token, int line)
            : ExprNode(line)
            , token(token)
        {
        }

        int getValue()
        {
            std::string stringValue = this->token.getValue();

            int value = std::stoi(stringValue);

            return value;
        }

        void accept(class Visitor &v);
};

#endif
