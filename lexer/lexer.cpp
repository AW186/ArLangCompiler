#include "lexer.hpp"
#include "rule.hpp"
#include <sstream>
#include <string>

Token::Token(int kind, string val) {
    this->mKind = kind;
    this->mVal = val;
}

int Token::getKind() {
    return mKind;
}

string Token::getVal() {
    return mVal;
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
    return new Token(kind[id], ss.str());
}