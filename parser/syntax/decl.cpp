#include "../syntax.hpp"
#include "decl.hpp"
#include <sstream>

using namespace std;

DeclSyntax::DeclSyntax(string type, string id) {
    mId = id;
    mType = type;
}

int DeclSyntax::getType() {
    return SYN_DECL;
}


void DeclSyntax::print() {
    cout << "Declare " << mId << " " << mType;
}

