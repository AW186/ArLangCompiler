#include "../syntax.hpp"
#include "forblk.hpp"
#include <sstream>

int loopID = 0;

int ForblkSyntax::getType() {
    return SYN_FORBLK;
}

ForblkSyntax::ForblkSyntax(LineSyntax *left, ExpSyntax *exp, LineSyntax *right, ExecBlockSyntax *blk) {
    this->mLeft = left;
    this->mRight = right;
    this->mExp = exp;
    this->mBlock = blk;
}

string ForblkSyntax::generateASM(ContextController *ctx) {
    ctx->push();
    stringstream ss;
    ss << this->mLeft->generateASM(ctx);
    stringstream loopss;
    loopss << "LOOP" << loopID++;
    string loop = loopss.str();
    ss << loop << ":" << endl;
    int reg = 200;
    ss << this->mExp->generateASM(ctx, reg);
    cout << "for exp gen done" << endl;
    ss << ctx->updateZS(new RegisterValue(reg));
    cout << "for exp gen done" << endl;
    ss << ctx->cjump("END" + loop);
    cout << "for exp gen done" << endl;
    ss << this->mBlock->generateASM(ctx);
    ss << this->mRight->generateASM(ctx) ;
    ss << ctx->jump(loop);
    ss << "END" << loop << ":";
    return ss.str();
}

void ForblkSyntax::print() {
    cout << "For (";
    this->mLeft->print();
    this->mExp->print();
    this->mRight->print();
    cout << ")";
    this->mBlock->print();
}

void ForblkSyntax::fixLiteral(vector<string> & lines) {
    if (this->mLeft) this->mLeft->fixLiteral(lines);
    if (this->mExp) this->mExp->fixLiteral(lines);
    if (this->mRight) this->mRight->fixLiteral(lines);
    if (this->mRight) this->mBlock->fixLiteral(lines);
}





