#include "lexer.hpp"
#include "reader.hpp"
#include "rule.hpp"
#include <iostream>

using namespace std;

int main() {
    Lexer *lex = new Lexer(new FileReader("test.al"), makeArLangRule());
    for (Token *t = lex->nextToken(); t->getKind() > END; t = lex->nextToken()) {
        cout << t->getKind() << ": " << t->getVal() << endl;
        delete t;
    }
    return 0;
}