#include "../syntax.hpp"
#include "ifblk.hpp"
#include <sstream>

int ifCount = 0;
int endifCount = 0;

ElseblkSyntax::ElseblkSyntax(ExecBlockSyntax *blk) {
    this->mBlock = blk;
}

int ElseblkSyntax::getType() {
    return SYN_ELSEBLK;
}
string ElseblkSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    ss << this->mBlock->generateASM(ctx);
    ss << "jmp endif" << endifCount << endl;              //jmp endif#
    return ss.str();
}

void ElseblkSyntax::print() {
    cout << "Else ";
    this->mBlock->print();
}

ElseifblkSyntax::ElseifblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el) {
    mExp = exp;
    mBlock = blk;
    mElse = el;
}

int ElseifblkSyntax::getType() {
    return SYN_ELIFBLK;
}
string ElseifblkSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    int reg;
    stringstream iflabelss;
    iflabelss << "if" << ifCount;
    string iflabel = iflabelss.str();                       
    ss << this->mExp->generateASM(ctx, reg);                //exp
    ss << ctx->updateZS(new RegisterValue(reg));            //add reg, 0
    ss << ctx->cjump(iflabel);                              //jnz if#
    if (this->mElse) ss << this->mElse->generateASM(ctx);   //else block
    ss << iflabel << ":" << endl;                           //if#:
    ss << this->mBlock->generateASM(ctx);                   //if block
    ss << "jmp endif" << endifCount << endl;              //jmp endif#
    return ss.str();
}

void ElseifblkSyntax::print() {
    cout << "Elseif " << "(";
    this->mExp->print();
    cout << ")";
    this->mBlock->print();
}

IfblkSyntax::IfblkSyntax(ExpSyntax *exp, ExecBlockSyntax *blk, AbstractElseSyntax *el) {
    mExp = exp;
    mBlock = blk;
    mElse = el;
}

int IfblkSyntax::getType() {
    return SYN_IFBLK;
}

string IfblkSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    int reg;
    stringstream iflabelss;
    iflabelss << "if" << ifCount;
    string iflabel = iflabelss.str();                       
    ss << this->mExp->generateASM(ctx, reg);                //exp
    ss << ctx->updateZS(new RegisterValue(reg));            //add reg, 0
    ss << ctx->cjump(iflabel);                              //jnz if#
    if (this->mElse) ss << this->mElse->generateASM(ctx);   //else block
    ss << iflabel << ":" << endl;                           //if#:
    ss << this->mBlock->generateASM(ctx);                   //if block
    ss << "endif" << endifCount++ << ":" << endl;           //endif#:
    return ss.str();
}

void IfblkSyntax::print() {
    cout << "if " << "(";
    this->mExp->print();
    cout << ")";
    this->mBlock->print();
}
void IfblkSyntax::fixLiteral(vector<string> & lines) {
    if (this->mExp) this->mExp->fixLiteral(lines);
    if (this->mBlock) this->mBlock->fixLiteral(lines);
    if (this->mElse) this->mElse->fixLiteral(lines);
}
void ElseifblkSyntax::fixLiteral(vector<string> & lines) {
    if (this->mExp) this->mExp->fixLiteral(lines);
    if (this->mBlock) this->mBlock->fixLiteral(lines);
    if (this->mElse) this->mElse->fixLiteral(lines);
}
void ElseblkSyntax::fixLiteral(vector<string> & lines) {
    if (this->mBlock) this->mBlock->fixLiteral(lines);
}




