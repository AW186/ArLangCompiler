#include "../syntax.hpp"
#include "exp.hpp"
#include <sstream>

ExpSyntax::ExpSyntax(AbstractSyntax *lexp, TokenSyntax *op, ExpSyntax *rexp) {
    this->mVal = lexp;
    this->mOp = op;
    this->mExp = rexp;
}

ExpSyntax:: ExpSyntax(AbstractSyntax *data) {
    this->mVal = data;
    this->mOp = NULL;
    this->mExp = NULL;
}

int ExpSyntax::getType() {
    return SYN_EXP;
}

void ExpSyntax::print() {
    cout << "Exp(";
    this->mVal->print();
    if (this->mOp) {
        cout << ", ";
        this->mOp->print();
        cout << ", ";
        this->mExp->print();
    }
    cout << ")";
}

ExpsSyntax::ExpsSyntax(ExpSyntax *exp, ExpsSyntax *next) {
    this->mExp = exp;
    this->mNext = next;
}

int ExpsSyntax::getType() {
    return SYN_EXPS;
}

void ExpsSyntax::print() {
    cout << "Exps (";
    this->mExp->print();
    if (this->mNext) this->mNext->print();
    cout << ")";
}

