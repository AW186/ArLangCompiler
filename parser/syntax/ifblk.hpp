#ifndef IFBLK_HPP
#define IFBLK_HPP

#include "../syntax.hpp"

class AbstractElseSyntax: public AbstractSyntax {

};

class ElseblkSyntax: public AbstractElseSyntax {
private:
    ExecBlockSyntax *mBlock;
public:
    ElseblkSyntax(ExecBlockSyntax *blk);
    llvm::Value * codegen() override;
    int getType() override;
    string generateASM(ContextController *ctx) override;
    void print() override;
    void fixLiteral(vector<string> & lines) override;
};

class ElseifblkSyntax: public AbstractElseSyntax {
private:
    ExpSyntax *mExp;
    ExecBlockSyntax *mBlock;
    AbstractElseSyntax *mElse;
public:
    ElseifblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el = NULL);
    llvm::Value * codegen() override;
    int getType() override;
    string generateASM(ContextController *ctx) override;
    void print() override;
    void fixLiteral(vector<string> & lines) override;
};

class IfblkSyntax: public AbstractLineContentSyntax {
private:
    ExpSyntax *mExp;
    ExecBlockSyntax *mBlock;
    AbstractElseSyntax *mElse;
public:
    IfblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el = NULL);
    llvm::Value * codegen() override;
    int getType() override;
    string generateASM(ContextController *ctx) override;
    void print() override;
    void fixLiteral(vector<string> & lines) override;
};

#endif
