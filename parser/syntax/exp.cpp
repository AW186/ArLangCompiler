#include "../syntax.hpp"
#include <sstream>

ExpSyntax::ExpSyntax(AbstractSyntax *lexp, TokenSyntax *op, ExpSyntax *rexp) {
    this->mVal = lexp;
    this->mOp = op;
    this->mExp = rexp;
}

ExpSyntax::ExpSyntax(AbstractSyntax *data) {
    this->mVal = data;
    this->mOp = NULL;
    this->mExp = NULL;
}

int ExpSyntax::getType() {
    return SYN_EXP;
}

string ExpSyntax::generateASM(ContextController *ctx, int &reg) {
    cout << "exp generate asm" << endl;
    stringstream ss;
    switch (this->mVal->getType() )
    {
    case SYN_IMM:
        ss << ctx->useRegisterForImm(this->mVal->getSymbol().name, reg) << endl;
        break;
    case SYN_ID:
        ss << ctx->useRegisterForCopy(this->mVal->getSymbol().name, reg, 0) << endl;
        break;
    case SYN_CALL:
        ss << this->mVal->generateASM(ctx);
        reg = _RAX;
        break;
    default:
        break;
    }
    if (!this->mOp) {
        cout << ss.str() << endl;
        return ss.str();
    }
    switch (this->mOp->getToken()->getKind())
    {
    case OR:
        return ctx->bwor(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    case XOR:
        return ctx->bwxor(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    case AND:
        return ctx->bwand(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    case PLUS:
        return ctx->add(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    case MINUS:
        return ctx->minus(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    case TIMES:
        return ctx->multiply(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    case DIV:
        return ctx->div(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    case EQUAL:
        return ctx->assign(new RegisterValue(reg), new SymbolValue(this->mVal->getSymbol().name));
    
    default:
        break;
    }
    cout << "exp generate asm done" << endl;
}

string ExpSyntax::generateASM(ContextController *ctx) {
    int reg;
    return generateASM(ctx, reg);
}

void ExpSyntax::print() {
    cout << "Exp(";
    this->mVal->print();
    if (this->mOp) {
        cout << ", ";
        this->mOp->print();
        cout << ", ";
        this->mExp->print();
    }
    cout << ")";
}

ExpsSyntax::ExpsSyntax(ExpSyntax *exp, ExpsSyntax *next) {
    this->mExp = exp;
    this->mNext = next;
}

int ExpsSyntax::getType() {
    return SYN_EXPS;
}
#define CALLEESAVE_PLHD (8 * 7)         //rip plus six callee saved register times 8
string ExpsSyntax::generateASMReg(ContextController *ctx, int index) {
    stringstream ss;
    cout << "gen asm reg" << endl;
    ss << "mov " << registerStrings[index] << ", [rsp-" << (CALLEESAVE_PLHD + index * 8) << "]" << endl;
    
    cout << "gen asm reg" << endl;
    if (this->mNext) ss << this->mNext->generateASMReg(ctx, index+1);
    return ss.str();
}
string ExpsSyntax::generateASM(ContextController *ctx, int index) {
    stringstream ss;
    int reg;
    ss << this->mExp->generateASM(ctx, reg);
    ss << "mov [rsp-" << (CALLEESAVE_PLHD + index * 8) << "], " << registerStrings[reg] << endl;
    if (this->mNext) ss << this->mNext->generateASM(ctx, index+1);
    return ss.str();
}

string ExpsSyntax::generateASM(ContextController *ctx) {
    return generateASM(ctx, 0);
}   

void ExpsSyntax::print() {
    cout << "Exps (";
    this->mExp->print();
    if (this->mNext) this->mNext->print();
    cout << ")";
}