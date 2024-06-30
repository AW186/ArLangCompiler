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
