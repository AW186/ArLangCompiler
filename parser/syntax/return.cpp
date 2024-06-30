#include "../syntax.hpp"
#include <sstream>
#include "../../semantic/context.hpp"
#include "return.hpp"

ReturnSyntax::ReturnSyntax(ExpSyntax * exp) : mExp(exp) {
}
int ReturnSyntax::getType() {
    return SYN_RET;
}

void ReturnSyntax::print() {
    cout << "return ";
    mExp->print();
}
