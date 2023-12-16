
#ifndef RETURN_HPP
#define RETURN_HPP

#include "abstractSyntax.hpp"
#include "exp.hpp"
#include <iostream>

using namespace std;

class ReturnSyntax: public AbstractSyntax {
    ExpSyntax *mExp;
public:
    explicit ReturnSyntax(ExpSyntax * exp);
    int getType() override;
    string generateASM(ContextController *ctx) override;
    void print() override;
};

#endif
