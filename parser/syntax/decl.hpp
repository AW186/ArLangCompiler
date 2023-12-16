#ifndef DECL_HPP
#define DECL_HPP

#include "abstractSyntax.hpp"
#include "execBlock.hpp"

class DeclSyntax: public AbstractLineContentSyntax {
    string mId;
    string mType;
public:
    DeclSyntax(string type, string id);
    int getType() override;
    string generateASM(ContextController *ctx) override;
    Symbol getSymbol() override;
    void print() override;
    void declaration(vector<string> & lines) override;
    void fixLiteral(vector<string> & lines) override;
};

#endif
