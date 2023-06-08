#include "../syntax.hpp"

DeclSyntax::DeclSyntax(string type, string id) {
    mId = id;
    mType = type;
}

int DeclSyntax::getType() {
    return SYN_DECL;
}