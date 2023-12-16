#include "../syntax.hpp"
#include "decl.hpp"
#include <sstream>

using namespace std;

DeclSyntax::DeclSyntax(string type, string id) {
    mId = id;
    mType = type;
}

int DeclSyntax::getType() {
    return SYN_DECL;
}

string DeclSyntax::generateASM(ContextController *ctx) {
    stringstream ss;
    if (ctx) {
        ss << ctx->addSymbol(Symbol {typeFromStr(this->mType), this->mId}) << endl;
        return ss.str();
    }
    return ss.str();
}

Symbol DeclSyntax::getSymbol() {
    return Symbol {typeFromStr(this->mType), this->mId};
}

void DeclSyntax::print() {
    cout << "Declare " << mId << " " << mType;
}

void DeclSyntax::declaration(vector<string> & lines) {
    lines.push_back(this->getSymbol().name);
}

void DeclSyntax::fixLiteral(vector<string> & lines) {
}

