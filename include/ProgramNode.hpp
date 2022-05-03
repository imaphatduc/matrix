#ifndef PROGRAM_NODE_HPP
#define PROGRAM_NODE_HPP

#include "AstNode.hpp"
#include "StatementNode.hpp"
#include <memory>
#include <vector>

class ProgramNode : public AstNode {
    private:
        std::vector<std::unique_ptr<StatementNode>> statementNodes;

    public:
        ProgramNode(int line)
            : AstNode(line)
        {
        }

        /* std::vector<std::unique_ptr<StatementNode>> getStatementNodes() */
        /* { */
        /*     return this->statementNodes; */
        /* } */

        void addStatementNode(std::unique_ptr<StatementNode> statementNode);

        void accept(class Visitor &v);
};

#endif
