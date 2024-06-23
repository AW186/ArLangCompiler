#ifndef ABSTRACT_SYNTAX_HPP
#define ABSTRACT_SYNTAX_HPP

#include <iostream>
#include <llvm/IR/Value.h>
#include <string>
#include <vector>
#include "../../semantic/context.hpp"

using namespace std;
/*
namespace llvm {
    struct Value {
        int x;
    };
}
*/

class AbstractSyntax {
public:
    virtual llvm::Value * codegen();
    virtual int getType() = 0;
    virtual string generateASM(ContextController *ctx) = 0;
    virtual Symbol getSymbol();
    virtual void fixLiteral(vector<string> & lines);
    virtual void declaration(vector<string> & lines);
    virtual void print();
};

#endif
