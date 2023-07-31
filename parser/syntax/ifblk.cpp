#include "../syntax.hpp"

ElseblkSyntax::ElseblkSyntax(ExecBlockSyntax *blk) {
    this->mBlock = blk;
}

int ElseblkSyntax::getType() {
    return SYN_ELSEBLK;
}

ElseifblkSyntax::ElseifblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el) {
    mExp = exp;
    mBlock = blk;
    mElse = el;
}

int ElseifblkSyntax::getType() {
    return SYN_ELIFBLK;
}

IfblkSyntax::IfblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el) {
    mExp = exp;
    mBlock = blk;
    mElse = el;
}

int IfblkSyntax::getType() {
    return SYN_IFBLK;
}