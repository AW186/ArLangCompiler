#ifndef LEXER_HPP
#define LEXER_HPP

#include "reader.hpp"
#include "rule.hpp"
#include <iostream>
#include <vector>

using namespace std;


class Token {
    int mKind;
    string mVal;
public:
    Token(int kind, string val);
    int getKind();
    string getVal();
};
//Interface:
class Lexer {
private:
    bool carry = false;
    char buffer = 0;
    Reader *mReader;
    vector<State *> mRule;
public:
    Lexer(Reader *reader, vector<State *> rule) {
        mReader = reader;
        mRule = rule;
    }
    Token *nextToken();
};

#endif