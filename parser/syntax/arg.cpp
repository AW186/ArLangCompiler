#include "../syntax.hpp"

ArgsSyntax::ArgsSyntax(string type, string id, ArgsSyntax *next) {
    mType = type;
    mId = id;
}

int ArgsSyntax::getType() {
    return SYN_ARGS;
}