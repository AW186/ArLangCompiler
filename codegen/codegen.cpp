
#include "codegen.hpp"
#include "../parser/syntax.hpp"
#include <llvm/IR/Constants.h>
#include <string>


static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<IRBuilder<>> Builder;
static std::unique_ptr<Module> TheModule;
static std::map<std::string, llvm::Value *> NamedValues;

static void InitializeModule() {
  // Open a new context and module.
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("my cool jit", *TheContext);
  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
}



llvm::Value *LogErrorV(const char *Str) {
  return nullptr;
}

llvm::Value * ArgsSyntax::codegen() {
    return nullptr;
}

llvm::Value * DeclSyntax::codegen() {
    return nullptr;
}
llvm::Value * LinesSyntax::codegen() {
    return nullptr;
}
llvm::Value * LineSyntax::codegen() {
    return nullptr;
}
llvm::Value * ExecBlockSyntax::codegen() {
    return nullptr;
}
llvm::Value * ExpsSyntax::codegen() {
    return nullptr;
}
llvm::Value * ExpSyntax::codegen() {
    auto left = this->mVal->codegen();
    if (this->mOp) {
        auto right = this->mExp->codegen();
        if (!left || !right) return nullptr;
        switch (this->mOp->getType()) {
            case OR:
                return Builder->CreateOr(left, right);
            case XOR:
                return Builder->CreateXor(left, right);
            case AND:
                return Builder->CreateAnd(left, right);
            case PLUS:
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
                break;
            default:
                break;
        }
    }
    return left;
}
llvm::Value * FileSyntax::codegen() {
    return nullptr;
}
llvm::Value * ForblkSyntax::codegen() {
    return nullptr;
}
llvm::Value * CallSyntax::codegen() {
    return nullptr;
}
llvm::Value * FuncSyntax::codegen() {
    return nullptr;
}
llvm::Value * IfblkSyntax::codegen() {
    return nullptr;
}
llvm::Value * ElseifblkSyntax::codegen() {
    return nullptr;
}
llvm::Value * ElseblkSyntax::codegen() {
    return nullptr;
}
llvm::Value * ProgramSyntax::codegen() {
    return nullptr;
}
llvm::Value * ReturnSyntax::codegen() {
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
            return NamedValues[this->mToken->getVal()];
        default:
            return LogErrorV("wrong token");
    }
}
















