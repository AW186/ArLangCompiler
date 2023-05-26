#include "../syntax.hpp"


LineSyntax::LineSyntax(string id, ExpSyntax *exp) {
    this->mType = SYN_ASSIGN;
    this->u.assign.exp = exp;
    this->u.assign.id = id.c_str();
}

LineSyntax::LineSyntax(int type, void *data) {
    this->mType = type;
    switch (type)
    {
    case SYN_EXP:
        this->u.exp = (ExpSyntax *)data;
        break;
    case SYN_DECL:
        this->u.decl = (DeclSyntax *)data;
    default:
        break;
    }
}

int LineSyntax::getType() {
    return SYN_LINE;
}

LinesSyntax::LinesSyntax(LineSyntax *line, LinesSyntax *next) {
    this->mLine = line;
    this->mNext = next;
}

int LinesSyntax::getType() {
    return SYN_LINES;
}

ExecBlockSyntax::ExecBlockSyntax(LinesSyntax *lines) {
    this->mLines = lines;
}

int ExecBlockSyntax::getType() {
    return SYN_BLOCK;
}