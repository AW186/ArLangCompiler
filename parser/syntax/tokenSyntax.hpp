#ifndef TOKEN_SYNTAX_HPP
#define TOKEN_SYNTAX_HPP

#include "abstractSyntax.hpp"
#include <iostream>
#include "../../lexer/lexer.hpp"

using namespace std;

class TokenSyntax: public AbstractSyntax {
private:
    Token *mToken;
    int mType;
public:
    TokenSyntax(Token *token);
    int getType() override;
    Token *getToken();
    string generateASM(ContextController *ctx) override;
    Symbol getSymbol() override;
    void print() override;
};

#endif