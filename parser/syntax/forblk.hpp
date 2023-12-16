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
    int getType() override;
    ForblkSyntax(LineSyntax *left, ExpSyntax *mExp, LineSyntax *right, ExecBlockSyntax *blk);
    string generateASM(ContextController *ctx) override;
    void print() override;
    void fixLiteral(vector<string> & lines) override;
};


#endif
