#ifndef IFBLK_HPP
#define IFBLK_HPP

#include "../syntax.hpp"

class AbstractElseSyntax: public AbstractSyntax {

};

class ElseblkSyntax: public AbstractElseSyntax {
private:
    ExecBlockSyntax *mBlock;
public:
    int getType() override;
    ElseblkSyntax(ExecBlockSyntax *blk);
};

class ElseifblkSyntax: public AbstractElseSyntax {
private:
    ExpSyntax *mExp;
    ExecBlockSyntax *mBlock;
    AbstractElseSyntax *mElse;
public:
    int getType() override;
    ElseifblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el = NULL);
};

class IfblkSyntax: public AbstractLineContentSyntax {
private:
    ExpSyntax *mExp;
    ExecBlockSyntax *mBlock;
    AbstractElseSyntax *mElse;
public:
    int getType() override;
    IfblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el = NULL);
};

#endif