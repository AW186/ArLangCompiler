#include "lexer.hpp"
#include "rule.hpp"
#include <sstream>
#include <string>
#include <map>


// |&^!+-*(){}[];=
static bool initializedID = false;
static map<string, int> idMap;
map<string, int> getIdMap() {
    if (initializedID) return idMap;
    initializedID   = true;
    idMap["if"]     = IF;
    idMap["else"]   = ELSE;
    idMap["for"]    = FOR;
    idMap["while"]  = WHILE;
    return idMap;
}

static bool initializedOP = false;
static map<char, int> opMap;
map<char, int> getOpMap() {
    if (initializedOP) return opMap;
    initializedOP = true;
    opMap['|'] = OR;
    opMap['&'] = AND;
    opMap['^'] = XOR;
    opMap['!'] = NOT;
    opMap['+'] = PLUS;
    opMap['-'] = MINUS;
    opMap['*'] = TIMES;
    opMap['/'] = DIV;
    opMap['('] = LBRKT;
    opMap[')'] = RBRKT;
    opMap['{'] = LPAREN;
    opMap['}'] = RPAREN;
    opMap[';'] = ENDL;
    opMap['='] = EQUAL;
    opMap['<'] = LESS;
    opMap['>'] = GREATER;
    opMap[','] = COMMA;
    return opMap;
}

int getKindWithStr(int kind, string val) {
    switch (kind)
    {
    case OPRAND:
        return getOpMap()[val[0]];
    case ID:
        if (getIdMap().count(val)) return getIdMap()[val];
    default:
        return kind;
    }
    return kind;
}

Token::Token(int kind, string val) {
    this->mKind = getKindWithStr(kind, val);
    this->mVal = val;
}

int Token::getKind() {
    return mKind;
}

string Token::getVal() {
    return mVal;
}

void Token::replaceImm(string val) {
    if (this->mKind == INTMED) this->mVal = val;
}

Token *Lexer::nextToken() {
    char c;
    stringstream ss;
    State *st = 0;
    int id = 0;
    if (this->carry && this->buffer == EOF) {
        return new Token(END, "");
    }
    for (st = mRule[0]; st; 
        st = (st && st->edge.toId >= 0) ? mRule[st->edge.toId] : NULL){
        if (this->carry) { 
            c = this->buffer;
            this->carry = false;
        } else c = this->mReader->getc();
        for (;st && !check(st->edge.condition, (uint8_t)c); st = st->pNextEdge);
        
        if (st) {
            ss << c;
            id = st->edge.toId;
        } else {
            this->buffer = c;
            this->carry = true;
        }
    }
    // cout << "end " << id << endl;
    if (kind[id] == IGNORE) return nextToken();
    return new Token(kind[id], ss.str());
}
