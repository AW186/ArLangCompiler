#include <stdio.h>
#include "../syntax.hpp"
#include "program.hpp"

#include <sstream>
#include <iostream>
using namespace std;

int ProgramSyntax::getType() {
    return SYN_PROGRAM;
}

ProgramSyntax::ProgramSyntax(AbstractSyntax *data, ProgramSyntax *next) {
    this->mContent = data;
    this->mNext = next;
}

void ProgramSyntax::print() {
    cout << "Content: " << this->mContent->getType() << endl;
    this->mContent->print();
    cout << endl;
    if (this->mNext) this->mNext->print();
}

