#include "../syntax.hpp"
#include <sstream>
#include "../../semantic/context.hpp"
#include "return.hpp"

ReturnSyntax::ReturnSyntax(ExpSyntax * exp) : mExp(exp) {
}
int ReturnSyntax::getType() {
    return SYN_RET;
}
string ReturnSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    int retreg;
    ss << this->mExp->generateASM(ctx, retreg);
    RegisterValue reg(retreg);
    RegisterValue rax(_RAX);
    ss << ctx->mov(&rax, &reg);
    return ss.str();
}

void ReturnSyntax::print() {
    cout << "return ";
    mExp->print();
}
