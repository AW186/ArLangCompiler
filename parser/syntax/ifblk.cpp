#include "../syntax.hpp"
#include "ifblk.hpp"
#include <sstream>

int ifCount = 0;
int endifCount = 0;

ElseblkSyntax::ElseblkSyntax(ExecBlockSyntax *blk) {
    this->mBlock = blk;
}

int ElseblkSyntax::getType() {
    return SYN_ELSEBLK;
}

void ElseblkSyntax::print() {
    cout << "Else ";
    this->mBlock->print();
}

ElseifblkSyntax::ElseifblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el) {
    mExp = exp;
    mBlock = blk;
    mElse = el;
}

int ElseifblkSyntax::getType() {
    return SYN_ELIFBLK;
}


void ElseifblkSyntax::print() {
    cout << "Elseif " << "(";
    this->mExp->print();
    cout << ")";
    this->mBlock->print();
}

IfblkSyntax::IfblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el) {
    mExp = exp;
    mBlock = blk;
    mElse = el;
}

int IfblkSyntax::getType() {
    return SYN_IFBLK;
}

void IfblkSyntax::print() {
    cout << "if " << "(";
    this->mExp->print();
    cout << ")";
    this->mBlock->print();
}
