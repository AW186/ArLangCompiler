#include "../syntax.hpp"
#include "func.hpp"
#include <sstream>

FuncSyntax::FuncSyntax(string type, string id, ArgsSyntax *args, ExecBlockSyntax *blk) {
    mType = type;
    mId = id;
    mBlock = blk;
    mArgs = args;
}

int FuncSyntax::getType() {
    return SYN_FUNC;
}

void FuncSyntax::print() {
    cout << "FUNC(";
    this->mArgs->print();
    cout << ") => " << this->mType  << endl;
    this->mBlock->print();
}

CallSyntax::CallSyntax(string id, ExpsSyntax *exps) {
    mId = id;
    mExps = exps;
}

int CallSyntax::getType() {
    return SYN_CALL;
}

void CallSyntax::print() {
    cout << "Call " << this->mId << "(";
    this->mExps->print();
    cout << ")";
}

