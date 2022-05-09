#ifndef LLVM_VISITOR_HPP
#define LLVM_VISITOR_HPP

#include "ExprNode.hpp"
#include "Visitor.hpp"
#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <memory>

class LLVMVisitor : public Visitor {
    private:
        llvm::raw_fd_ostream &out;

        llvm::LLVMContext &llvmContext;
        std::unique_ptr<llvm::Module> &llvmModule;
        llvm::IRBuilder<> llvmBuilder;

        llvm::Value *llvmValue;

    public:
        LLVMVisitor(llvm::raw_fd_ostream &out, llvm::LLVMContext &llvmContext, std::unique_ptr<llvm::Module> &llvmModule)
            : out(out)
            , llvmContext(llvmContext)
            , llvmModule(llvmModule)
            , llvmBuilder(llvmContext)
            , llvmValue(nullptr)
        {
        }

        void visit(ProgramNode *node);
        void visit(StatementNode *node);
        void visit(ExprNode *node);
        void visit(IntegerNode *node);
        void visit(DoubleNode *node);
        void visit(BinaryExprNode *node);
};

#endif
