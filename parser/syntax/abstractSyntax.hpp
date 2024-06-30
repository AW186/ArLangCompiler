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
    virtual void print();
};

#endif
