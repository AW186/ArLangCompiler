#ifndef ABSTRACT_SYNTAX_HPP
#define ABSTRACT_SYNTAX_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../../semantic/context.hpp"

using namespace std;

class AbstractSyntax {
public:
    virtual int getType() = 0;
    virtual string generateASM(ContextController *ctx) = 0;
    virtual Symbol getSymbol();
    virtual void fixLiteral(vector<string> & lines);
    virtual void declaration(vector<string> & lines);
    virtual void print();
};

#endif
