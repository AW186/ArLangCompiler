#include "parser/parser.hpp"
#include <fstream>
#include <map>
#include <iostream>
#include <sstream>

void printMapping(map<int, int> dict) {
    for (auto it = dict.begin(); it != dict.end(); it++) {
        printf("%d, %d\n", (*it).first, (*it).second);
    }
}

int main(int argc, char * argv[]) {
    if (argc < 2) {
        printf("please enter a file\n");
        return -1;
    }
    printf("start compile\n");
    LRTable *table = getDefaultLRTable();
    printf("table generated\n");
    printMapping(table->getMapping());
    auto syntax = makeSyntaxTree(new Lexer(new FileReader(argv[1]), makeArLangRule()), table->getTable(), table->getMapping());
    cout << "type " << syntax->getType() << endl;
    syntax->print();
    syntax->codegen();
}
