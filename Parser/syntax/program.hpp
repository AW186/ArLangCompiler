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
    int mType;
    ProgramU u;
    ProgramSyntax *mNext;
public:
    ProgramSyntax(int type, void *data, ProgramSyntax *next);
    int getType() override;
};

#endif