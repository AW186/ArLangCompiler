#include "../syntax.hpp"
#include "forblk.hpp"
#include <sstream>

int loopID = 0;

int ForblkSyntax::getType() {
    return SYN_FORBLK;
}

ForblkSyntax::ForblkSyntax(LineSyntax *left, ExpSyntax *exp, LineSyntax *right, ExecBlockSyntax *blk) {
    this->mLeft = left;
    this->mRight = right;
    this->mExp = exp;
    this->mBlock = blk;
}

void ForblkSyntax::print() {
    cout << "For (";
    this->mLeft->print();
    this->mExp->print();
    this->mRight->print();
    cout << ")";
    this->mBlock->print();
}





