#include "arg.hpp"
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


void ArgsSyntax::print() {
    cout << "args " << mId << " " << mType << ", ";
    if (this->mNext) this->mNext->print();
}

size_t ArgsSyntax::size() {
    return 1 + (mNext ? mNext->size() : 0);
}

ArgsSyntax * ArgsSyntax::next() {
    return mNext;
}

string ArgsSyntax::getName() {
    return mId;
}
