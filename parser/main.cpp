#include "parser.hpp"
#include <map>

void printMapping(map<int, int> dict) {
    for (auto it = dict.begin(); it != dict.end(); it++) {
        printf("%d, %d\n", (*it).first, (*it).second);
    }
}

int main() {
    LRTable *table = getDefaultLRTable();
    printf("table generated\n");
    printMapping(table->getMapping());
    makeSyntaxTree(new Lexer(new FileReader("../lexer/test.al"), makeArLangRule()), table->getTable(), table->getMapping());
}