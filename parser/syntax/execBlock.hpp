#ifndef EXEC_BLOCK
#define EXEC_BLOCK

#include "exp.hpp"
#include "decl.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

class LineSyntax: public AbstractSyntax {
    int mType;
    union {
        DeclSyntax *decl;
        ExpSyntax *exp;
        struct {
            char const *id;
            ExpSyntax *exp;
        } assign;
    } u;
public:
    LineSyntax(string id, ExpSyntax *exp);
    LineSyntax(int type, void *data);
    int getType() override;
};


class LinesSyntax: public AbstractSyntax {
    LineSyntax *mLine;
    LinesSyntax *mNext;
public:
    LinesSyntax(LineSyntax *line, LinesSyntax *next);
    int getType() override;
};

class ExecBlockSyntax: public AbstractSyntax {
    LinesSyntax *mLines;
public:
    ExecBlockSyntax(LinesSyntax *lines);
    int getType() override;
};


#endif