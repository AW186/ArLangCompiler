#include "../syntax.hpp"
#include "func.hpp"
#include <sstream>

FuncSyntax::FuncSyntax(string type, string id, ArgsSyntax *args, ExecBlockSyntax *blk) {
    mType = type;
    mId = id;
    mBlock = blk;
    mArgs = args;
}

int FuncSyntax::getType() {
    return SYN_FUNC;
}

string FuncSyntax::generateASM(ContextController *ctx) {
    cout << "func generate asm" << endl;
    stringstream ss;
    ss << ctx->declareFunc(this->mId);
    ss << ctx->saveCallee();
    ss << this->mArgs->generateASM(ctx);
    ss << this->mBlock->generateASM(ctx);
    ss << ctx->popCallee();
    return ss.str();
}

void FuncSyntax::print() {
    cout << "FUNC(";
    this->mArgs->print();
    cout << ") => " << this->mType  << endl;
    this->mBlock->print();
}

Symbol FuncSyntax::getSymbol() {
    return Symbol { FUNC, this->mId };
}

CallSyntax::CallSyntax(string id, ExpsSyntax *exps) {
    mId = id;
    mExps = exps;
}

string CallSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    ss << ctx->saveCaller();
    ss << this->mExps->generateASM(ctx);
    if (this->mId == "syscall") {
        ss << this->mExps->generateASMReg(ctx, -1);
        ss << "syscall" << endl;
    } else {
        ss << this->mExps->generateASMReg(ctx, -1);
        ss << ctx->call(this->mId);
    }
    ss << ctx->popCaller();
    return ss.str();
}

int CallSyntax::getType() {
    return SYN_CALL;
}

void CallSyntax::print() {
    cout << "Call " << this->mId << "(";
    this->mExps->print();
    cout << ")";
}

void CallSyntax::fixLiteral(vector<string> & lines) {
    this->mExps->fixLiteral(lines);
}

void FuncSyntax::fixLiteral(vector<string> & lines) {
    cout << "fixing func" << endl;
    this->mBlock->fixLiteral(lines);
}

void FuncSyntax::declaration(vector<string> & lines) {
    lines.push_back(this->getSymbol().name);
}








