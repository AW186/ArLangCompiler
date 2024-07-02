#include "../syntax.hpp"
#include "func.hpp"
#include <sstream>

ProtoSyntax::ProtoSyntax(string type, string id, ArgsSyntax *args) {
    mType = type;
    mId = id;
    mArgs = args;
}

void ProtoSyntax::print() {
    cout << "FUNC(";
    this->mArgs->print();
    cout << ") => " << this->mType  << endl;
}

int ProtoSyntax::getType() {
    return SYN_FUNC;
}

size_t ProtoSyntax::argsSize() {
    return this->mArgs ? this->mArgs->size() : 0;
}

FuncSyntax::FuncSyntax(string type, string id, ArgsSyntax *args, ExecBlockSyntax *blk) {
    proto = new ProtoSyntax(type, id, args);
    mId = id;
    mBlock = blk;
}

int FuncSyntax::getType() {
    return SYN_FUNC;
}

void FuncSyntax::print() {
    this->proto->print();
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

size_t FuncSyntax::argsSize() {
    return this->proto->argsSize();
}
