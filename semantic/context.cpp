#include "context.hpp"
#include <string.h>
#include <iostream>
#include <sstream>

string registerStrings[16] = {
    "rax",
    "rbx",
    "rcx",
    "rdx",
    "rsi",
    "rdi",
    "rbp",
    "rsp",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15"
};

string registerStringsByte[16] = {
    "al",
    "bl",
    "cl",
    "sil",
    "dil",
    "bpl",
    "spl",
    "spl",
    "r8b",
    "r9b",
    "r10b",
    "r11b",
    "r12b",
    "r13b",
    "r14b",
    "r15b"
};
int typeSize[1] = {
    8
};

map<string, int> typeMap;
void initMap() {
    typeMap["int"] = INT;
    typeMap["string"] = STRING;
    typeMap["func"] = FUNC;
}
int typeFromStr(string str) {
    if (!typeMap.count(str)) {
        initMap();
    }
    return typeMap[str];
}

Context::Context() {
    mSymbolList = map<string, Symbol>(); //local symbol list
    mlst = map<string, Address>();      //local symbol table, on stack
    mlsybolRegMap = map<string, int>();
    mgst = map<string, Symbol>();               //global symbol table, linker will resolve this
    mParent = NULL;
    mLastUse = vector<uint64_t>(16);
    mRegisters = vector<string>(16);
    mOffset = 0;
    mBase = 0;
}
Context::Context(map<string, Symbol> gst, Context *parent): Context() {
    this->mgst = gst;
    this->mParent = parent;
    this->mBase = mParent ? mParent->mBase + mParent->mOffset : 0;
}
void Context::addSymbol(Symbol sybl) {
    this->mSymbolList[sybl.name] = sybl;
    this->mlst[sybl.name] = Address {mBase, mOffset};
    mOffset += typeSize[sybl.type];
}
int Context::getOffset() {
    return mOffset;
}

map<string, Symbol> Context::getGST() {
    return mgst;
}
SymbolRep Context::getSymbol(string sybl) {
    SymbolRep res;
    if (mSymbolList.count(sybl)) {
        if (mRegisters[mlsybolRegMap[sybl]] == sybl) {
            res.type = REG;
            res.u.reg = mlsybolRegMap[sybl];
            this->mLastUse[mlsybolRegMap[sybl]] = mLine++;
            return res;
        } else {
            res.type = ADDR;
            res.u.addr = mlst[sybl];
            return res;
        }
    }
    res.type = NONE;
    if (mParent) {
        res = mParent->getSymbol(sybl);
    }
    if (res.type == NONE && this->mgst.count(sybl)) {
        res.type = SYBL;
    }
    return res;
}
Context * Context::pop() {
    return this->mParent;
}
string Context::retrieveRegister(int mask, int &reg){
    mask |= (1 << _RSP) | (1 << _RBP);
    reg = -1;
    uint64_t min = INT64_MAX;
    for (int i = 0; i < 16; i++) {
        if (mask & (1 << i)) continue;
        if (min > this->mLastUse[i]) {
            min = this->mLastUse[i];
            reg = i;
        }
    }
    if (reg == -1) return "";
    stringstream ss;
    if (!this->mRegisters[reg].empty() && getSymbol(this->mRegisters[reg]).type == ADDR) {
        auto val = new SymbolValue(this->mRegisters[reg]);
        ss << "    mov " << val->toString(this) << ", " << registerStrings[reg] << endl;
    }
    this->mRegisters[reg] = "";
    return ss.str();
}
string Context::useRegisterFor(string sybl, int &reg) {
    auto rep = this->getSymbol(sybl);
    switch (rep.type) {
        case NONE:
            reg = -1;
            return "";
        case REG:
            reg = rep.u.reg;
            return "";
    }
    cout << "ctx use reg" << endl;
    string res = retrieveRegister(0, reg);
    cout << "ctx use reg 2" << endl;
    mlsybolRegMap[sybl] = reg;
    this->mRegisters[reg] = sybl;
    updateUseReg(reg);
    return res;
}

void Context::updateUseReg(int reg) {
    this->mLastUse[reg] = mLine++;
}
/*******************************************************************
 *          Values
*******************************************************************/

RegisterValue::RegisterValue(int reg) {
    this->mReg = reg;
}
string RegisterValue::toString(Context *ctx) {
    cout << "reg 2 string " << mReg << endl;
    ctx->updateUseReg(mReg);
    return registerStrings[mReg];
}

SymbolValue::SymbolValue(string sybl) {
    this->mSybl = sybl;
}

string toStackAddress(Address addr){
    stringstream ss;
    ss << "[rbp-" << (addr.base+addr.offset) << "]";
    return ss.str();
}
string SymbolValue::toString(Context *ctx) {
    cout << "Symbol 2 string" << endl;
    auto syblRep = ctx->getSymbol(this->mSybl);
    switch (syblRep.type)
    {
    case NONE:
        return "";
    case REG:
        return registerStrings[syblRep.u.reg];
    case ADDR:
        return toStackAddress(syblRep.u.addr);
    case SYBL:
        return this->mSybl;
    default:
        break;
    }
    return "";
}

/**********************************************************************
 *      Context Controller -- Intermediate Code
**********************************************************************/

ContextController::ContextController(map<string, Symbol> gst) {
    this->top = new Context(gst, NULL);
}

void ContextController::pop() {
    if (this->top) this->top = this->top->pop();
    else cout << "ERROR: can't pop" << endl;
}

void ContextController::push() {
    this->top = new Context(this->top->getGST(), this->top);
}

string ContextController::useRegisterForImm(string imm, int &reg) {
    stringstream ss;
    ss << this->top->retrieveRegister(0, reg) << endl;
    ss << "    mov " << registerStrings[reg] << ", " << imm << endl;
    return ss.str();
}
string ContextController::useRegisterFor(string sybl, int &reg) {
    auto rep = this->top->getSymbol(sybl);
    stringstream ss;
    switch (rep.type) {
        case NONE:
            reg = -1;
            ss << "ERROR: Symbol " << sybl << " isn't declared" << endl;
            return ss.str();
        case REG:
            reg = rep.u.reg;
            return "";
        case ADDR:
            ss << this->top->useRegisterFor(sybl, reg);
            ss << "    mov " << registerStrings[reg] << ", " << toStackAddress(rep.u.addr) << endl;
            return ss.str();
        case SYBL:
            ss << this->top->useRegisterFor(sybl, reg);
            ss << "    mov " << registerStrings[reg] << ", " << sybl << endl;
            return ss.str();
    }
    cout << "ERROR at use reg4" << endl;
    exit(-1);
}
string ContextController::useRegisterForCopy(string sybl, int &reg, int mask) {
    auto rep = this->top->getSymbol(sybl);
    stringstream ss;
    switch (rep.type) {
        case NONE:
            reg = -1;
            ss << "ERROR: Symbol " << sybl << " isn't declared" << endl;
            return ss.str();
        case REG:
            reg = rep.u.reg;
            return "";
        case ADDR:
            ss << this->top->retrieveRegister(mask, reg);
            ss << "    mov " << registerStrings[reg] << ", " << toStackAddress(rep.u.addr) << endl;
            return ss.str();
        case SYBL:
            ss << this->top->retrieveRegister(mask, reg);
            ss << "    mov " << registerStrings[reg] << ", " << sybl << endl;
            return ss.str();
    }
    cout << "ERROR at use reg4copy" << endl;
    exit(-1);
}

string ContextController::bnot(int regVal, int regRes) {
    stringstream ss;
    ss << "    xor " << registerStringsByte[regRes] << ", " << registerStringsByte[regRes] << endl;
    ss << "    cmp " << registerStrings[regVal] << ", 0" << endl;
    ss << "    sete " << registerStringsByte[regRes] << endl; 
    return ss.str();
}
string ContextController::mov(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    mov " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::addSymbol(Symbol sybl) {
    this->top->addSymbol(sybl);
    stringstream ss;
    ss << "    sub rsp, " << typeSize[sybl.type] << endl;
    return ss.str();
}
string ContextController::add(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    add " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::minus(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    sub " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::multiply(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    imul " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::div(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    idiv " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::bwand(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    and " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::bwor(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    or " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::bwxor(Value *val1, Value *val2) {
    stringstream ss;
    ss << "    xor " << val1->toString(this->top) << ", " << val2->toString(this->top) << endl;
    return ss.str();
}
string ContextController::assign(Value *val1, Value *val2) {
    return mov(val1, val2);
}
string ContextController::declareFunc(string sybl) {
    stringstream ss;
    ss << sybl << ":" << endl;
    return ss.str();
}
string ContextController::updateZS(Value *val) {
    stringstream ss;
    cout << "update zs" << endl;
    ss << "    add " << val->toString(this->top) << ", " << 0 << endl;
    cout << "update zs" << endl;
    return ss.str();
}
string ContextController::jump(string sybl) {
    stringstream ss;
    ss << "    jmp " << sybl << endl;
    return ss.str();
}
string ContextController::cjump(string sybl) {
    stringstream ss;
    ss << "    jnz " << sybl << endl;
    return ss.str();
}
string ContextController::call(string fn) {
    stringstream ss;
    ss << "    call " << fn << endl;
    return ss.str();
}
string ContextController::saveCaller() {
    stringstream ss;
    ss << "    push rax" << endl;
    ss << "    push rcx" << endl;
    ss << "    push rdx" << endl;
    ss << "    push rsi" << endl;
    ss << "    push rdi" << endl;
    ss << "    push r8" << endl;
    ss << "    push r9" << endl;
    ss << "    push r10" << endl;
    ss << "    push r11" << endl;
    return ss.str();
}
string ContextController::popCaller() {
    stringstream ss;
    ss << "    pop r11" << endl;
    ss << "    pop r10" << endl;
    ss << "    pop r9" << endl;
    ss << "    pop r8" << endl;
    ss << "    pop rdi" << endl;
    ss << "    pop rsi" << endl;
    ss << "    pop rdx" << endl;
    ss << "    pop rcx" << endl;
    ss << "    pop rax" << endl;
    return ss.str();
}
string ContextController::saveCallee() {

    stringstream ss;
    ss << "    push rbx" << endl;
    ss << "    push r12" << endl;
    ss << "    push r13" << endl;
    ss << "    push r14" << endl;
    ss << "    push r15" << endl;
    ss << "    push rbp" << endl;
    ss << "    mov rbp, rsp" << endl;
    return ss.str();
}
string ContextController::popCallee() {
    stringstream ss;
    ss << "    mov rsp, rbp" << endl;
    ss << "    pop rbp" << endl;
    ss << "    pop r15" << endl;
    ss << "    pop r14" << endl;
    ss << "    pop r13" << endl;
    ss << "    pop r12" << endl;
    ss << "    pop rbx" << endl;
    ss << "    ret" << endl;
    return ss.str();
}
