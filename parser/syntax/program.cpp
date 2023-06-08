#include <stdio.h>
#include "../syntax.hpp"

int ProgramSyntax::getType() {
    return SYN_PROGRAM;
}

ProgramSyntax::ProgramSyntax(AbstractSyntax *data, ProgramSyntax *next) {
    this->mContent = data;
    this->mNext = next;
}