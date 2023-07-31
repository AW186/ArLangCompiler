#ifndef RULE_HPP
#define RULE_HPP

#include <iostream>
#include <vector>

//Types:
#define NOTEND  -1
#define END     0
#define IF      1
#define ELSE    2
#define LPAREN  3
#define RPAREN  4
#define FOR     5
#define LBRKT   6
#define RBRKT   7
#define PLUS    8
#define MINUS   9
#define DIV     10
#define TIMES   11
#define WHILE   12
#define EQUAL   13
#define AND     14
#define OR      15
#define XOR     16
#define NOT     17
#define RET     18
#define ENDL    19
#define INTMED  20
#define TYPE    21
#define PRINT   22
#define ID      23
#define IGNORE  24
#define OPRAND  25
#define LESS    26
#define GREATER 27

#define MAXRULE 15
#define MASKBLKSIZE 32
#define MASKBLKID(n) (n / MASKBLKSIZE)
#define MASKOFFSET(n) (n % MASKBLKSIZE)
#define MASKDIGIT(n) (1 << MASKOFFSET(n))

using namespace std;
//Rule Header:
extern int kind[];


typedef struct mask {
    uint64_t mask[8];
} mask;

bool check(mask m, uint8_t index);
void printMask(mask m);
class State
{
public:
    int stateid;
    State *pNextEdge;
    struct {
        mask condition;
        int toId;
    } edge;
    State(int id, State *nextEdge, mask condition, int toId) {
        this->stateid = id;
        this->pNextEdge = nextEdge;
        this->edge.condition = condition;
        this->edge.toId = toId;
    }
};

//Rule:

vector<State *> makeArLangRule();

#endif