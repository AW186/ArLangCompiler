#ifndef EXEC_BLOCK
#define EXEC_BLOCK

#include <stdio.h>
#include <iostream>

using namespace std;

class AbstractLineContentSyntax: public AbstractSyntax {

};

class LineSyntax: public AbstractSyntax {
    int mType;
    AbstractLineContentSyntax *line;
public:
    LineSyntax(AbstractLineContentSyntax *data);
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