#ifndef EXP_HPP
#define EXP_HPP

#include <iostream>
#include "abstractSyntax.hpp"
#include "tokenSyntax.hpp"
#include "execBlock.hpp"

using namespace std;

class ExpSyntax: public AbstractLineContentSyntax {
    AbstractSyntax *mVal;
    TokenSyntax *mOp;
    ExpSyntax *mExp;
public:
    ExpSyntax(AbstractSyntax *data);
    ExpSyntax(AbstractSyntax *lexp, TokenSyntax *op, ExpSyntax *rexp);
    int getType() override;
};

class ExpsSyntax: public AbstractSyntax {
private:
    ExpSyntax *mExp;
    ExpsSyntax *mNext;
public:
    ExpsSyntax(ExpSyntax *exp, ExpsSyntax *next);
    int getType() override;
};

#endif