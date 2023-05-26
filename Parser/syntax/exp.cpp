#include "../syntax.hpp"

ExpSyntax::ExpSyntax(string exp) {
    this->mExp = exp;
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