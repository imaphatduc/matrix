#include "../include/LLVMVisitor.hpp"

void LLVMVisitor::visit(ProgramNode *node)
{
    // Function returns void.
    llvm::FunctionType *functionReturnType = llvm::FunctionType::get(llvm::Type::getVoidTy(this->llvmContext), false);

    // Main function.
    llvm::Function *mainFunction = llvm::Function::Create(functionReturnType,
        llvm::Function::ExternalLinkage,
        "main",
        this->llvmModule.get());

    // Basic block inside of mainFunction.
    llvm::BasicBlock *body = llvm::BasicBlock::Create(this->llvmContext, "body", mainFunction);
    this->llvmBuilder.SetInsertPoint(body);

    // Setup printf prototype.
    std::vector<llvm::Type *> params;
    params.push_back(llvm::Type::getInt8PtrTy(this->llvmContext));

    llvm::FunctionType *printfType = llvm::FunctionType::get(this->llvmBuilder.getInt32Ty(), params, /*isVarArg=*/true);
    llvm::Function::Create(printfType, llvm::Function::ExternalLinkage, "printf",
        this->llvmModule.get());

    // Visit all statements.
    for (auto &statement : node->getStatementNodes()) {
        statement->accept(*this);
    }

    // Return.
    this->llvmBuilder.CreateRetVoid();

    // Print to executable file.
    this->llvmModule->print(this->out, nullptr);
    this->out.close();
}

void LLVMVisitor::visit(StatementNode *node)
{
    node->getExprNode()->accept(*this);

    // Call printf with the returned value.
    std::vector<llvm::Value *> printArgs;

    llvm::Value *formatStr;

    formatStr = this->llvmBuilder.CreateGlobalStringPtr("%d\n");

    printArgs.push_back(formatStr);
    printArgs.push_back(this->llvmValue);

    llvmBuilder.CreateCall(this->llvmModule->getFunction("printf"), printArgs);
}

void LLVMVisitor::visit(ExprNode *node)
{
    node->accept(*this);
}

void LLVMVisitor::visit(IntegerNode *node)
{
    this->llvmValue = llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(this->llvmContext), node->getValue());
}

void LLVMVisitor::visit(DoubleNode *node)
{
    this->llvmValue = llvm::ConstantFP::get(llvm::Type::getDoubleTy(this->llvmContext), node->getValue());
}

void LLVMVisitor::visit(BinaryExprNode *node)
{
    node->getLeftExprNode()->accept(*this);
    llvm::Value *leftExprNode = this->llvmValue;

    node->getRightExprNode()->accept(*this);
    llvm::Value *rightExprNode = this->llvmValue;

    switch (node->getBinOp()) {
        case '+':
            this->llvmValue = this->llvmBuilder.CreateAdd(leftExprNode, rightExprNode, "addtmp");
            break;

        case '-':
            this->llvmValue = this->llvmBuilder.CreateSub(leftExprNode, rightExprNode, "subtmp");
            break;

        case '*':
            this->llvmValue = this->llvmBuilder.CreateMul(leftExprNode, rightExprNode, "multmp");
            break;

        case '/':
            this->llvmValue = this->llvmBuilder.CreateSDiv(leftExprNode, rightExprNode, "addtmp");
            break;

        default:
            break;
    }
}
