#include "abstractSyntax.hpp"

Symbol AbstractSyntax::getSymbol() {
    return Symbol { NOTSYBL, "Abstract" };
}

void AbstractSyntax::print() {
    cout << "Abstract Syntax" << endl;
}
void AbstractSyntax::fixLiteral(vector<string> & lines) {
    cout << "type " << getType() << " not implement fixLiteral" << endl;
    return;
}
void AbstractSyntax::declaration(vector<string> & lines) {
    cout << "type " << getType() << " not implement fixLiteral" << endl;
    return;

}

