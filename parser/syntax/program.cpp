#include <stdio.h>
#include "../syntax.hpp"

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

void ProgramSyntax::makeGST(map<string, Symbol> &gst) {
    gst[this->mContent->getSymbol().name] = this->mContent->getSymbol();
    if (this->mNext) this->mNext->makeGST(gst);
}

string ProgramSyntax::generateASM(ContextController *ctx) {
    if (!ctx) {
        cout << "program generate gst" << endl;
        map<string, Symbol> gst;
        this->makeGST(gst);
        ctx = new ContextController(gst);
    }
    cout << "program generate asm" << endl;
    stringstream ss;
    ss << this->mContent->generateASM(ctx) << endl;
    if (this->mNext) ss << this->mNext->generateASM(ctx);
    return ss.str();
}

void ProgramSyntax::print() {
    cout << "Content: " << this->mContent->getType() << endl;
    this->mContent->print();
    cout << endl;
    if (this->mNext) this->mNext->print();
}