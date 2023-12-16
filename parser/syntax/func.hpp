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
    int getType() override;
    string generateASM(ContextController *ctx) override;
    Symbol getSymbol() override;
    void print() override;
    void fixLiteral(vector<string> & lines) override;
    void declaration(vector<string> & lines) override;
};

class CallSyntax: public AbstractSyntax {
    string mId;
    ExpsSyntax *mExps;
public:
    CallSyntax(string id, ExpsSyntax *exps);
    int getType() override;
    string generateASM(ContextController *ctx) override;
    void print() override;
    void fixLiteral(vector<string> & lines) override;
};

#endif
