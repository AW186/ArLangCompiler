#ifndef FUNC_HPP
#define FUNC_HPP

#include "abstractSyntax.hpp"
#include "execBlock.hpp"
#include "exp.hpp"
#include "arg.hpp"
#include <iostream>

using namespace std;

class ProtoSyntax: public AbstractSyntax {
    string mType;
    string mId;
    ArgsSyntax *mArgs;
public:
    ProtoSyntax(string type, string id, ArgsSyntax *args);
    llvm::Value * codegen() override;
    int getType() override;
    void print() override;
    size_t argsSize();
};

class FuncSyntax: public AbstractSyntax {
    ProtoSyntax *proto;
    ExecBlockSyntax *mBlock;
    string mId;
public:
    FuncSyntax(string type, string id, ArgsSyntax *args, ExecBlockSyntax *blk);
    llvm::Value * codegen() override;
    int getType() override;
    void print() override;
    size_t argsSize();
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
