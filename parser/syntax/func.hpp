#ifndef FUNC_HPP
#define FUNC_HPP

#include "abstractSyntax.hpp"
#include "execBlock.hpp"
#include "exp.hpp"
#include "arg.hpp"
#include <iostream>

using namespace std;

class FuncSyntax: public AbstractSyntax {
    string mType;
    string mId;
    ExecBlockSyntax *mBlock;
    ArgsSyntax *mArgs;
public:
    FuncSyntax(string type, string id, ArgsSyntax *args, ExecBlockSyntax *blk);
    llvm::Value * codegen() override;
    int getType() override;
    void print() override;
};

class CallSyntax: public AbstractSyntax {
    string mId;
    ExpsSyntax *mExps;
public:
    CallSyntax(string id, ExpsSyntax *exps);
    llvm::Value * codegen() override;
    int getType() override;
    void print() override;
};

#endif
