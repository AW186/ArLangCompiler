#ifndef FILE_HPP
#define FILE_HPP

#include "../syntax.hpp"

class FileSyntax: public AbstractSyntax {
private:
    ProgramSyntax *mProgram;
public:
    FileSyntax(ProgramSyntax *program);
    int getType() override;
    llvm::Value * codegen() override;
    void print() override;
};

#endif
