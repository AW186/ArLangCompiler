#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <map>
#include <set>
#include <iostream>


using namespace std;

typedef struct Symbol {
    string name;
    int type;
} Symbol;

typedef struct Address {
    uint64_t base;
    uint64_t offset;
} Address;

class Context {
private:
    map<Symbol, Address> mlst;
    set<Symbol> mgst;
    Context *mParent;
    uint64_t mOffset;
    uint64_t newlst(map<Synbol, Address> mlst, uint64_t rsp);
public:
    Context(set<Symbol> gst, Context *parent);
    void addSymbol(Symbol sybl, Address addr);
    Address getSymbol(string sybl);
    Context *pop();
};


#define ESEM_COMP 0
#define ESEM_SING 1

class ExpSemantic {
public:
    ExpSemantic(Symbol *symbol);
    ExpSemantic(string *imm);
    ExpSemantic(ExpSemantic *left, int op, ExpSemantic *right);
    int type;
    union {
        struct {
            ExpSemantic *left;
            ExpSemantic *right;
        } compound;
        union {
            string imm;
            Symbol *sybl;
        } single;
    } u;
    int op;
};

class ContextController {
    Context *top;
public:
    ContextController(set<string> gst);
    void pop();
    void push();
    void addSymbol(Symbol sybl, Address addr);
    void assignSymbol();
    void jump(string sybl);
    void cjump(string sybl, ExpSemantic *cond);
    Address getSymbol(string sybl);
}

#endif