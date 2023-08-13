#include "abstractSyntax.hpp"

Symbol AbstractSyntax::getSymbol() {
    return Symbol { NOTSYBL, "Abstract" };
}

void AbstractSyntax::print() {
    cout << "Abstract Syntax" << endl;
}
