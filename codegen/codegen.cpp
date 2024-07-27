#include <fstream>
#include <iostream>
#include <llvm/IR/Constants.h>
#include <llvm/Support/raw_ostream.h>
#include <string>
#include "llvm/ADT/APFloat.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "codegen.hpp"

using namespace llvm;

llvm::Value *LogErrorV(const char *Str, int line) {
    cout << "Error at line " << line << ": " << Str << endl;
    return nullptr;
}

struct NamedValueStackNode {
    NamedValueStackNode * parent;
    llvm::Value * get(string name) {
        if (values.count(name)) return values[name];
        if (parent) return parent->get(name);
        return nullptr;
    }
    llvm::Value * set(string name, llvm::Value * val) {
        if (values.count(name)) return values[name] = val;
        else if (parent) return parent->set(name, val);
        else return values[name] = val;
    }
    bool count(string name) {
        return values.count(name) || (parent && parent->count(name));
    }
private:
    std::map<std::string, llvm::Value *> values;
};
class NamedValueStack {
    NamedValueStackNode * node;
public:
    NamedValueStack() {
        node = new NamedValueStackNode();
    }
    llvm::Value * set(string name, llvm::Value * val) {
        return node->set(name, val);
    }
    llvm::Value * get(string name) {
        return node->get(name);
    }
    bool count(string name) {
        return node->count(name);
    }
    void push() {
        auto new_node = new NamedValueStackNode();
        new_node->parent = node;
        node = new_node;
    }
    void pop() {
        auto parent = node->parent;
        delete node;
        node = parent;
    }
};

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<IRBuilder<>> Builder;
static std::unique_ptr<Module> TheModule;
static NamedValueStack * NamedValues;

static void InitializeModule(string filename) {
    // Open a new context and module.
    TheContext = std::make_unique<LLVMContext>();
    TheModule = std::make_unique<Module>(filename, *TheContext);
    // Create a new builder for the module.
    Builder = std::make_unique<IRBuilder<>>(*TheContext);
    NamedValues = new NamedValueStack();
}

llvm::Value * ArgsSyntax::codegen() {
    return nullptr;
}

llvm::Value * DeclSyntax::codegen() {
    cout << "Declare codegen" << endl;
    NamedValues->set(this->mId, nullptr);
    return nullptr;
}
llvm::Value * LinesSyntax::codegen() {
    cout << "Lines codegen" << endl;
    mLine->codegen();
    if (mNext) mNext->codegen();
    return nullptr;
}
llvm::Value * LineSyntax::codegen() {
    cout << "Line codegen" << endl;
    this->line->codegen();
    return nullptr;
}
llvm::Value * ExecBlockSyntax::codegen() {
    NamedValues->push();
    if (this->mLines) return this->mLines->codegen();
    NamedValues->pop();
    return nullptr;
}
llvm::Value * ExpsSyntax::codegen() {
    return nullptr;
}
llvm::Value * ExpSyntax::codegen() {
    cout << "exp codegen" << endl;
    this->print();
    cout << endl;
    auto left = this->mVal->codegen();
    if (this->mOp) {
        auto right = this->mExp->codegen();
        if (!right) return nullptr;
        cout << "op type " << this->mOp->getType() << endl;
        switch (this->mOp->getToken()->getKind()) {
            case OR:
                return Builder->CreateOr(left, right);
            case XOR:
                return Builder->CreateXor(left, right);
            case AND:
                return Builder->CreateAnd(left, right);
            case PLUS:
                cout << "make Add" << endl;
                if (!left) cout << "FAILED" << endl;
                return Builder->CreateFAdd(left, right);
            case MINUS:
                return Builder->CreateFSub(left, right);
            case TIMES:
                return Builder->CreateFMul(left, right);
            case DIV:
                return Builder->CreateFDiv(left, right);
            case EQUAL:
                if (mVal->getType() != SYN_ID) {
                    return nullptr;
                }
                if (!NamedValues->count(((TokenSyntax *)this->mVal)->getToken()->getVal())) return LogErrorV("Variable name undefined", __LINE__);
                return NamedValues->set(((TokenSyntax *)this->mVal)->getToken()->getVal(), right);
            default:
                cout << "failed to make exp" << endl;
                break;
        }
    }
    cout << "exp finished" << endl;
    return left;
}
llvm::Value * FileSyntax::codegen() {
    cout << "File codegen" << endl;
    this->mProgram->codegen();
    return nullptr;
}
llvm::Value * ForblkSyntax::codegen() {
    NamedValues->push();
    this->mLeft->codegen();
    Function *func = Builder->GetInsertBlock()->getParent();
    llvm::BasicBlock * loopstart = llvm::BasicBlock::Create(*TheContext, "loop", func);
    Builder->CreateBr(loopstart);
    Builder->SetInsertPoint(loopstart);

    llvm::Value *cond = this->mExp->codegen();
    if (!cond) return nullptr;
    cond = Builder->CreateFCmpONE(
            cond, ConstantFP::get(*TheContext, APFloat(0.0)), "loopcond");
    llvm::BasicBlock * loopblk = llvm::BasicBlock::Create(*TheContext, "loop", func);
    BasicBlock *afterblk = BasicBlock::Create(*TheContext, "else");

    Builder->CreateCondBr(cond, loopblk, afterblk);
    // Emit loop body
    Builder->SetInsertPoint(loopblk);
    this->mBlock->codegen();
    this->mRight->codegen();
    Builder->CreateBr(loopstart);
    // Emit else 
    func->insert(func->end(), afterblk);
    Builder->SetInsertPoint(afterblk);


    NamedValues->pop();
    return nullptr;
}
llvm::Value * CallSyntax::codegen() {
    llvm::Function * calleeFunc = TheModule->getFunction(this->mId);
    if (!calleeFunc) return LogErrorV("undefined reference", __LINE__);
    if (this->mExps ? this->mExps->size() != calleeFunc->arg_size() : calleeFunc->arg_size() == 0)
        return LogErrorV("wrong input size for callee func", __LINE__);
    std::vector<llvm::Value *> args;
    for (auto exp = this->mExps; exp; exp = exp->getNext()) {
        args.push_back(exp->getExp()->codegen());
        if (!args.back())
            return LogErrorV("failed to generate code for args", __LINE__);
    }
    cout << "call codegen" << endl;
    return Builder->CreateCall(calleeFunc, args, "calltemp");
}
llvm::Value * ProtoSyntax::codegen() {
    // Make the function type:  double(double,double) etc.
    cout << "Proto codegen" << endl;
    std::vector<Type*> Doubles(this->argsSize(),
            Type::getDoubleTy(*TheContext));
    FunctionType *FT =
        FunctionType::get(Type::getDoubleTy(*TheContext), Doubles, false);

    Function *func =
        Function::Create(FT, Function::ExternalLinkage, this->mId, TheModule.get());
    auto node = this->mArgs;
    for (auto &arg : func->args()) {
        arg.setName(node->getName());
        node = node->next();
    }

    return func;
}
llvm::Value * FuncSyntax::codegen() {
    cout << "Func codegen" << endl;
    llvm::Function * func = TheModule->getFunction(this->mId);
    if (!func) func = (llvm::Function *)this->proto->codegen();
    if (!func || !func->empty()) return LogErrorV("redefine or undefine", __LINE__);

    BasicBlock *blk = BasicBlock::Create(*TheContext, "entry", func);
    Builder->SetInsertPoint(blk);

    // Record the function arguments in the NamedValues map.
    for (auto &Arg : func->args()) {
        NamedValues->set(std::string(Arg.getName()), &Arg);
        cout << "set " << string(Arg.getName()) << endl;
    }

    this->mBlock->codegen();

    if (verifyFunction(*func)) {
        return func;
    }
    func->eraseFromParent();
    return nullptr;
}
llvm::Value * IfblkSyntax::codegen() {
    llvm::Value *cond = this->mExp->codegen();
    if (!cond) return nullptr;
    // Convert condition to a bool by comparing non-equal to 0.0.
    cond = Builder->CreateFCmpONE(
            cond, ConstantFP::get(*TheContext, APFloat(0.0)), "ifcond");
    Function *func = Builder->GetInsertBlock()->getParent();
    // Create blocks for the then and else cases.  Insert the 'then' block at the
    // end of the function.
    BasicBlock *thenblk = BasicBlock::Create(*TheContext, "then", func);
    BasicBlock *elseblk = BasicBlock::Create(*TheContext, "else");
    BasicBlock *mergeblk = BasicBlock::Create(*TheContext, "ifcont");

    Builder->CreateCondBr(cond, thenblk, elseblk);
    // Emit then
    Builder->SetInsertPoint(thenblk);
    this->mBlock->codegen();
    Builder->CreateBr(mergeblk);
    // Emit else 
    func->insert(func->end(), elseblk);
    Builder->SetInsertPoint(elseblk);
    if (mElse) this->mElse->codegen();
    Builder->CreateBr(mergeblk);
    // back to continue
    func->insert(func->end(), mergeblk);
    Builder->SetInsertPoint(mergeblk);

    return nullptr;
}

llvm::Value * ElseifblkSyntax::codegen() {
    llvm::Value *cond = this->mExp->codegen();
    if (!cond) return nullptr;
    // Convert condition to a bool by comparing non-equal to 0.0.
    cond = Builder->CreateFCmpONE(
            cond, ConstantFP::get(*TheContext, APFloat(0.0)), "ifcond");
    Function *func = Builder->GetInsertBlock()->getParent();
    // Create blocks for the then and else cases.  Insert the 'then' block at the
    // end of the function.
    BasicBlock *thenblk = BasicBlock::Create(*TheContext, "then", func);
    BasicBlock *elseblk = BasicBlock::Create(*TheContext, "else");
    BasicBlock *mergeblk = BasicBlock::Create(*TheContext, "ifcont");

    Builder->CreateCondBr(cond, thenblk, elseblk);
    // Emit then
    Builder->SetInsertPoint(thenblk);
    this->mBlock->codegen();
    Builder->CreateBr(mergeblk);
    // Emit else 
    func->insert(func->end(), elseblk);
    Builder->SetInsertPoint(elseblk);
    if (mElse) this->mElse->codegen();
    Builder->CreateBr(mergeblk);
    // back to continue
    func->insert(func->end(), mergeblk);
    Builder->SetInsertPoint(mergeblk);

    return nullptr;
}
llvm::Value * ElseblkSyntax::codegen() {
    this->mBlock->codegen();
    return nullptr;
}
llvm::Value * ProgramSyntax::codegen() {
    cout << "Program codegen" << endl;
    this->mContent->codegen();
    if (mNext) this->mNext->codegen();
    return nullptr;
}
llvm::Value * ReturnSyntax::codegen() {
    if (auto res = this->mExp->codegen())
        return Builder->CreateRet(res);
    return nullptr;
}
/*
 *    switch (this->mVal->getType() )
    {
    case SYN_IMM:
        ss << ctx->useRegisterForImm(this->mVal->getSymbol().name, reg) << endl;
        cout << "reg " << reg << endl;
        break;
    case SYN_ID:
        ss << ctx->useRegisterForCopy(this->mVal->getSymbol().name, reg, 0) << endl;
        cout << "reg " << reg << endl;
        break;
    case SYN_CALL:
        ss << this->mVal->generateASM(ctx);
        reg = _RAX;
        cout << "reg " << reg << endl;
        break;
    case SYN_EXP:
        ss << ((ExpSyntax *)(this->mVal))->generateASM(ctx, reg) << endl;
    default:
        break;
    }
 */
llvm::Value * TokenSyntax::codegen() {
    switch (this->getType()) {
        case SYN_IMM:
            return ConstantFP::get(*TheContext, APFloat(stof(this->mToken->getVal())));
        case SYN_ID:
            return NamedValues->get(this->mToken->getVal());
        default:
            return LogErrorV("wrong token", __LINE__);
    }
}


void codegen_dump(FileSyntax * file, string src_path, string dst_path) {
    string s;
    raw_string_ostream ss(s);
    ofstream dumpfile;
    dumpfile.open(dst_path);
    InitializeModule(src_path);
    file->codegen();
    TheModule->print(ss, nullptr);
    dumpfile << ss.str();
    cout << ss.str() << endl;
    dumpfile.close();
}














