#include "../syntax.hpp"

int ForblkSyntax::getType() {
    return SYN_FORBLK;
}
ForblkSyntax::ForblkSyntax(LineSyntax *left, ExpSyntax *exp, LineSyntax *right, ExecBlockSyntax *blk) {
    this->mLeft = left;
    this->mRight = right;
    this->mExp = exp;
    this->mBlock = blk;
}
