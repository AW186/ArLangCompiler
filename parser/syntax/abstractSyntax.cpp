#include "abstractSyntax.hpp"


void AbstractSyntax::print() {
    cout << "Abstract Syntax" << endl;
}

llvm::Value * AbstractSyntax::codegen() {
    return nullptr;
}
