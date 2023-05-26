#include <stdio.h>
#include "../syntax.hpp"

int ProgramSyntax::getType() {
    return SYN_PROGRAM;
}

ProgramSyntax::ProgramSyntax(int type, void *data, ProgramSyntax *next) {
    this->mType = type;
    this->mNext = next;
    switch (type)
    {
    case SYN_FUNC:
        this->u.func = (FuncSyntax *)data;
        break;
    case SYN_STRUCT:
        this->u.stct = (StructSyntax *)data;
        break;
    case SYN_DECL:
        this->u.decl = (DeclSyntax *)data;
        break;
    default:
        printf("Not valid program\n");
        break;
    }
}