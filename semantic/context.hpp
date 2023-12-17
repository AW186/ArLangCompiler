#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <map>
#include <set>
#include <iostream>
#include <cstdint>
#include <vector>

#define _RAX 0
#define _RBX 1
#define _RCX 2
#define _RDX 3
#define _RSI 4
#define _RDI 5
#define _RBP 6
#define _RSP 7
#define _R8  8
#define _R9  9
#define _R10 10
#define _R11 11
#define _R12 12
#define _R13 13
#define _R14 14
#define _R15 15

#define NONE 0
#define REG  1
#define ADDR 2
#define SYBL 3

using namespace std;


#define NOTSYBL -1
#define INT     0
#define STRING   1
#define FUNC    2

int typeFromStr(string str);

extern int typeSize[];
extern string registerStrings[];
extern string registerStringsByte[];

typedef struct Symbol {
    int type;
    string name;
} Symbol;

typedef struct Address {
    uint64_t base;
    uint64_t offset;
} Address;

string toStackAddress(Address addr, int offset);

typedef struct SymbolRep {
    union {
        int reg;
        Address addr;
    } u;
    int type;
} SymbolRep;

class Context {
private:
    int mLine = 0;
    vector<uint64_t> mLastUse;

    map<string, Symbol> mSymbolList; //local symbol list
    map<string, Address> mlst;      //local symbol table, on stack
    map<string, int> mlsybolRegMap;
    map<string, Symbol> mgst;               //global symbol table, linker will resolve this
    Context *mParent;
    vector<string> mRegisters;
    uint64_t mOffset;
    uint64_t mBase;
public:
    Context();
    Context(map<string, Symbol> gst, Context *parent);
    void addSymbol(Symbol sybl);
    SymbolRep getSymbol(string sybl);
    void updateUseReg(int reg);
    string useRegisterFor(string sybl, int &reg);
    string retrieveRegister(int mask, int &reg);
    int getOffset();
    map<string, Symbol> getGST();
    Context *pop();
};

class Value {
public:
    virtual string toString(Context *ctx) = 0;
};

class RegisterValue: public Value {
    int mReg;
public:
    RegisterValue(int reg);
    string toString(Context *ctx) override;
};

class SymbolValue: public Value {
    string mSybl;
public:
    SymbolValue(string sybl);
    string toString(Context *ctx) override;
};

class ContextController {
    Context *top;
    int argc = 0;
public:
    ContextController(map<string, Symbol> gst);
    void pop();
    void push();
    string useRegisterForImm(string imm, int &reg);
    string useRegisterFor(string sybl, int &reg);
    string useRegisterForCopy(string sybl, int &reg, int mask);
    string bnot(int regVal, int regRes);
    string mov(Value *val1, Value *val2);
    string addSymbol(Symbol sybl);
    string declArg(Symbol sybl);
    string assignArg(bool first);
    string add(Value *val1, Value *val2);
    string minus(Value *val1, Value *val2);
    string multiply(Value *val1, Value *val2);
    string div(Value *val1, Value *val2);
    string bwand(Value *val1, Value *val2l);
    string bwor(Value *val1, Value *val2);
    string bwxor(Value *val1, Value *val2);
    string assign(Value *val1, Value *val2);
    string declareFunc(string sybl);
    string updateZS(Value *val);
    string jump(string sybl);
    string cjump(string sybl);
    string call(string fn);
    string saveCaller();
    string popCaller();
    string saveCallee();
    string popCallee();
    string generateGlobalFunc();
    string generateGlobalVar();
};

#endif
