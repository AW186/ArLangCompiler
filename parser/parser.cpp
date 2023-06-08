#include "parser.hpp"
#include <deque>
#include "reduction.hpp"


#define FAIL  0
#define SHIFT 1
#define GOTO  2
#define REDUCE 3
#define ACCEPT 4
stackblk makeStackBlk(int state, AbstractSyntax *data) {
    stackblk blk;
    blk.data = data;
    blk.state = state;
    return blk;
}

AbstractSyntax *makeSyntaxTree(Lexer *lex, vector<vector<action>> lrtable, map<int, int> mapping) {
    int state = 0;
    deque<stackblk> stack;
    stackblk buffer;
    TokenSyntax *c = new TokenSyntax(lex->nextToken());
    printf("token %d: %s\n", c->getType(), c->getToken()->getVal().c_str());
    AbstractSyntax *next = c;
    while (1) {
        action act = lrtable[state][mapping[next->getType()]];
        printf("action %d %d\n", act.type, act.num);
        switch (act.type)
        {
        case FAIL:
            printf("Syntax error on state %d, with entry %d\n", state, next->getType());
            exit(-1);
        case SHIFT:
            state = act.num;
            stack.push_back(makeStackBlk(state, next));
            c = new TokenSyntax(lex->nextToken());
            next = c;
            printf("token %d: %s\n", c->getType(), c->getToken()->getVal().c_str());
            break;
        case GOTO:
            state = act.num;
            buffer.state = state;
            stack.push_back(buffer);
            next = c;
            break;
        case REDUCE:
            buffer = reduce[act.num](stack);
            next = buffer.data;
            state = !stack.empty() ? stack.back().state : 0;
            break;
        case ACCEPT:
            return stack.front().data;
        default:
            break;
        }
    }
    return NULL;
}
