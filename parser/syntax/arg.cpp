#include "../syntax.hpp"
#include <sstream>
#include <iostream>
using namespace std;

ArgsSyntax::ArgsSyntax(string type, string id, ArgsSyntax *next) {
    mType = type;
    mId = id;
    mNext = next;
}

int ArgsSyntax::getType() {
    return SYN_ARGS;
}

string ArgsSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    ss << ctx->addSymbol(Symbol {typeFromStr(this->mType), this->mId}) << endl;
    return ss.str();
}

void ArgsSyntax::print() {
    cout << "args " << mId << " " << mType << ", ";
    if (this->mNext) this->mNext->print();
}