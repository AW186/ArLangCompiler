#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "abstractSyntax.hpp"
#include "func.hpp"
#include "decl.hpp"


class ProgramSyntax: public AbstractSyntax {
private:
    AbstractSyntax *mContent;
    ProgramSyntax *mNext;
public:
    ProgramSyntax(AbstractSyntax *data, ProgramSyntax *next);
    llvm::Value * codegen() override;
    int getType() override;
    void print() override;
};

#endif
