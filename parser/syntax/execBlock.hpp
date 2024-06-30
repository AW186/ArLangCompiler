#ifndef EXEC_BLOCK
#define EXEC_BLOCK

#include <stdio.h>
#include <iostream>
#include "abstractSyntax.hpp"
using namespace std;

class AbstractLineContentSyntax: public AbstractSyntax {

};

class LineSyntax: public AbstractSyntax {
    int mType;
    AbstractLineContentSyntax *line;
public:
    llvm::Value * codegen() override;
    LineSyntax(AbstractLineContentSyntax *data);
    int getType() override;
    void print() override;
};


class LinesSyntax: public AbstractSyntax {
    LineSyntax *mLine;
    LinesSyntax *mNext;
public:
    llvm::Value * codegen() override;
    LinesSyntax(LineSyntax *line, LinesSyntax *next);
    int getType() override;
    void print() override;
};

class ExecBlockSyntax: public AbstractSyntax {
    LinesSyntax *mLines;
public:
    llvm::Value * codegen() override;
    ExecBlockSyntax(LinesSyntax *lines);
    int getType() override;
    void print() override;
};


#endif
