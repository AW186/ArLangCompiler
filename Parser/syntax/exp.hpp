#ifndef EXP_HPP
#define EXP_HPP

#include <iostream>
#include "abstractSyntax.hpp"

using namespace std;

class ExpSyntax: public AbstractSyntax {
    string mExp;
public:
    ExpSyntax(string exp);
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