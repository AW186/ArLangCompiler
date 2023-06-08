#include "../syntax.hpp"

ExpSyntax::ExpSyntax(ExpSyntax *lexp, TokenSyntax *op, ExpSyntax *rexp) {
    this->mVal = lexp;
    this->mOp = op;
    this->mExp = rexp;
}

ExpSyntax::ExpSyntax(AbstractSyntax *data) {
    this->mVal = data;
}

int ExpSyntax::getType() {
    return SYN_EXP;
}

ExpsSyntax::ExpsSyntax(ExpSyntax *exp, ExpsSyntax *next) {
    this->mExp = exp;
    this->mNext = next;
}

int ExpsSyntax::getType() {
    return SYN_EXPS;
}