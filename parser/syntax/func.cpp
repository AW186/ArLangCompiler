#include "../syntax.hpp"

FuncSyntax::FuncSyntax(string type, string id, ArgsSyntax *args, ExecBlockSyntax *blk) {
    mType = type;
    mId = id;
    mBlock = blk;
    mArgs = args;
}

int FuncSyntax::getType() {
    return SYN_FUNC;
}

CallSyntax::CallSyntax(string id, ExpsSyntax *exps) {
    mId = id;
    mExps = exps;
}

int CallSyntax::getType() {
    return SYN_CALL;
}