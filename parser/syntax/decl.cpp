#include "../syntax.hpp"
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
    ss << this->mId << ": dq 0" << endl;
}

Symbol DeclSyntax::getSymbol() {
    return Symbol {typeFromStr(this->mType), this->mId};
}

void DeclSyntax::print() {
    cout << "Declare " << mId << " " << mType;
}
