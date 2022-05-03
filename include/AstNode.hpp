#ifndef AST_NODE_HPP
#define AST_NODE_HPP

class AstNode {
    private:
        int line { 0 };

    public:
        AstNode(int line)
            : line(line)
        {
        }

        int getLine()
        {
            return this->line;
        }

        virtual void accept(class Visitor &v) = 0;
};

#endif
