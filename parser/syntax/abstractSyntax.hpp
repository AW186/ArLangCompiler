#ifndef ABSTRACT_SYNTAX_HPP
#define ABSTRACT_SYNTAX_HPP

#include <iostream>
#include "../../semantic/context.hpp"

using namespace std;

class AbstractSyntax {
public:
    virtual int getType() = 0;
    virtual string generateASM(ContextController *ctx) = 0;
    virtual Symbol getSymbol();
    virtual void print();
};

#endif