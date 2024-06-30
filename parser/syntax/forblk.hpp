#ifndef FORBLK_HPP
#define FORBLK_HPP

#include "execBlock.hpp"
#include "exp.hpp"

class ForblkSyntax: public AbstractLineContentSyntax {
private:
    ExpSyntax *mExp;
    LineSyntax *mLeft;
    LineSyntax *mRight;
    ExecBlockSyntax *mBlock;
public:
    ForblkSyntax(LineSyntax *left, ExpSyntax *mExp, LineSyntax *right, ExecBlockSyntax *blk);
    int getType() override;
    llvm::Value * codegen() override;
    void print() override;
};


#endif
