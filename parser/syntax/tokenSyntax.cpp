#include "../syntax.hpp"
#include <vector>
#include <set>
//|&^!+-*/(){}[];=

static bool vinitialized = false;
static vector<int> synMap(28);
static bool sinitialized = false;
static set<string> types;

set<string> getTypes() {
    if (sinitialized) return types;
    sinitialized = true;
    types.insert("int");
    types.insert("string");
    types.insert("void");
    return types;
}

vector<int> getSynMap() {
    if (vinitialized) return synMap;
    vinitialized = true;
    synMap[OR] = SYN_OP;
    synMap[AND] = SYN_OP;
    synMap[XOR] = SYN_OP;
    synMap[NOT] = SYN_OP;
    synMap[PLUS] = SYN_OP;
    synMap[MINUS] = SYN_OP;
    synMap[TIMES] = SYN_OP;
    synMap[DIV] = SYN_OP;
    synMap[LBRKT] = SYN_LBR;
    synMap[RBRKT] = SYN_RBR;
    synMap[LPAREN] = SYN_LPREN;
    synMap[RPAREN] = SYN_RPREN;
    synMap[ENDL] = SYN_ENDL;
    synMap[EQUAL] = SYN_ASSIGN;
    synMap[END] = SYN_END;
    synMap[ID] = SYN_ID;
    synMap[INTMED] = SYN_IMM;
    synMap[FOR] = SYN_FOR;
    synMap[IF] = SYN_IF;
    synMap[ELSE] = SYN_ELSE;
    synMap[LESS] = SYN_OP;
    synMap[GREATER] = SYN_OP;
    synMap[COMMA] = SYN_COMMA;
    return synMap;
};


TokenSyntax::TokenSyntax(Token *token) {
    this->mToken = token;
    this->mType = getSynMap()[token->getKind()];
    printf("token type %d mType: %d val %s\n", token->getKind(), this->mType, token->getVal().c_str());
    if (this->mType == SYN_ID && getTypes().count(token->getVal()))
        this->mType = SYN_TYPE;
}

int TokenSyntax::getType() {
    return this->mType;
}

Token *TokenSyntax::getToken() {
    return mToken;
}
    
string TokenSyntax::generateASM(ContextController *ctx) {
    return "token should not generate ASM\n";
}


Symbol TokenSyntax::getSymbol() {
    return Symbol {
        0,
        this->mToken->getVal()
    };
}

void TokenSyntax::print() {
    cout << "token {" << this->mType << ", " << this->mToken->getVal() << "}";
}