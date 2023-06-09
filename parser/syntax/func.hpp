#ifndef FUNC_HPP
#define FUNC_HPP

#include "abstractSyntax.hpp"
#include "execBlock.hpp"
#include "exp.hpp"
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
};

class CallSyntax: public AbstractSyntax {
    string mId;
    ExpsSyntax *mExps;
public:
    CallSyntax(string id, ExpsSyntax *exps);
    int getType() override;
};

#endif