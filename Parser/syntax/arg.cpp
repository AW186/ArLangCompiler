#include "../syntax.hpp"

Args::Args(string type, string id, Args *next) {
    mType = type;
    mId = id;
}

int Args::getType() {
    return SYN_ARGS;
}