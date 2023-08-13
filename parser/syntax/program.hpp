#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "abstractSyntax.hpp"
#include "func.hpp"
#include "decl.hpp"

union ProgramU {
    FuncSyntax *func;
    StructSyntax *stct;
    DeclSyntax *decl;
};

class ProgramSyntax: public AbstractSyntax {
private:
    AbstractSyntax *mContent;
    ProgramSyntax *mNext;
public:
    ProgramSyntax(AbstractSyntax *data, ProgramSyntax *next);
    int getType() override;
    string generateASM(ContextController *ctx) override;
    void makeGST(map<string, Symbol> &gst);
    void print() override;
};

#endif