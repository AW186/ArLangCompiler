
#ifndef RETURN_HPP
#define RETURN_HPP

#include "execBlock.hpp"
#include "exp.hpp"
#include <iostream>

using namespace std;

class ReturnSyntax: public AbstractLineContentSyntax{
    ExpSyntax *mExp;
public:
    explicit ReturnSyntax(ExpSyntax * exp);
    llvm::Value * codegen() override;
    int getType() override;
    void print() override;
};

#endif
