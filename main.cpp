#include "include/LLVMVisitor.hpp"
#include "include/Lexer.hpp"
#include "include/Parser.hpp"
#include "include/ProgramNode.hpp"
#include <cstdlib>
#include <iostream>
#include <llvm/ADT/StringRef.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <string>
#include <vector>

void printHelp();
void printVersion();

std::string getFileContent(char *fileName);

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Too few arguments\n";

        return 1;
    }

    char *inFileName;
    std::string compiledFileName = "a.out";

    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];

        if (arg[0] == '-') {
            std::string flag = arg.substr(1, std::string::npos);

            if (flag == "h" || flag == "-help") {
                printHelp();

                return 0;
            }

            if (flag == "v" || flag == "-version") {
                printVersion();

                return 0;
            }

            if (flag == "o" || flag == "-output") {
                compiledFileName = argv[i + 1];
            }

            continue;
        }

        inFileName = argv[i];
        i -= 1;
    }

    std::string inFileContents = getFileContent(inFileName);

    Lexer lexer;

    std::vector<Token> tokens = lexer.tokenizer(inFileContents);

    Parser parser;

    auto program = parser.parse(tokens);

    llvm::LLVMContext llvmContext;
    auto llvmModule = std::make_unique<llvm::Module>("Matrix language module", llvmContext);

    std::string irCompilerName = "clang++";
    std::string irFileName = "out.ll";

    llvm::StringRef irRef = irFileName;
    std::error_code ec;
    llvm::raw_fd_ostream out(irRef, ec);

    LLVMVisitor visitor(out, llvmContext, llvmModule);

    program->accept(visitor);

    std::system(irCompilerName.append(" ").append(irFileName).append(" -o ").append(compiledFileName).append(" && rm ").append(irFileName).data());

    return 0;
}

void printHelp()
{
    std::cout << "Usage: matc [options] [file]\n";
    std::cout << "Options:\n";
    std::cout << "-h, --help        Display this message\n";
    std::cout << "-v, --version     Display Matrix version information\n";
    std::cout << "-o FILENAME       Write output to <FILENAME>\n";
    std::cout << '\n';
}

void printVersion()
{
    std::cout << "matc v0.0.1\n";
}

std::string getFileContent(char *fileName)
{
    FILE *fh = fopen(fileName, "r");

    if (!fh) {
        std::cerr << "Cannot find file.\n";
    }

    fseek(fh, 0, SEEK_END);

    size_t fileSize = ftell(fh);

    fseek(fh, 0, SEEK_SET);

    std::string fileContents(fileSize, ' ');

    fread(fileContents.data(), 1, fileSize, fh);

    return fileContents;
}
