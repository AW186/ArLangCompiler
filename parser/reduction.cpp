
#include "reduction.hpp"
#include <stdio.h>
#include <deque>
/*
/FILE>/PROGRAM/END
/ARGS>/TYPE/ID/COMMA/ARGS
/ARGS>/TYPE/ID
/LINES>/LINE/LINES
/LINES>/LINE
/BLOCK>/LPREN/LINES/RPREN
/FUNC>/TYPE/ID/LBR/ARGS/RBR/BLOCK
/PROGRAM>/FUNC/PROGRAM
/PROGRAM>/DECL/PROGRAM
/DECL>/TYPE/ID/ENDL
/DECL>/TYPE/ID/ASSIGN/IMM/ENDL
/DEF>/TYPE/ID/ASSIGN/EXP/ENDL
/LINE>/DECL
/LINE>/DEF
/LINE>/ID/ASSIGN/EXP/ENDL
/LINE>/EXP/ENDL
/CALL>/ID/LBR/EXPS/RBR
/EXPS>/EXP/COMMA/EXPS
/EXPS>/EXP
/EXP>/LBR/EXP/OP/EXP/RBR
/EXP>/ID
/EXP>/IMM
/EXP>/CALL
*/

#define BLOCK_T(s)      ((ExecBlockSyntax *)(s.data))
#define LINES_T(s)      ((LinesSyntax *)(s.data))
#define LINE_T(s)       ((LineSyntax *)(s.data))
#define EXPS_T(s)       ((ExpsSyntax *)(s.data))
#define EXP_T(s)        ((ExpSyntax *)(s.data))
#define TOKEN_T(s)      ((TokenSyntax *)(s.data))
#define ARGS_T(s)       ((ArgsSyntax *)(s.data))
#define FUNC_T(s)       ((FuncSyntax *)(s.data))
#define DECL_T(s)       ((DeclSyntax *)(s.data))
#define CALL_T(s)       ((CallSyntax *)(s.data))
#define PROGRAM_T(s)    ((ProgramSyntax *)(s.data))

stackblk pop(deque<stackblk> &stack) {
    stackblk res = stack.back();
    stack.pop_back();
    return res;
}

stackblk pop(deque<stackblk> &stack, int type) {
    stackblk res = pop(stack);
    if (res.data->getType() != type) {
        printf("TYPE ERROR: expecting %d, but have %d\n", type, res.data->getType());
    }
    return res;
}

// /FILE>/PROGRAM/END
stackblk r0(deque<stackblk> &stack) {
    printf("accepted\n");
    auto entry = stack.front();
    stack.pop_back();
    return entry;
}
// /ARGS>/TYPE/ID/COMMA/ARGS
stackblk r1(deque<stackblk> &stack) {
    stackblk res;
    auto args = pop(stack, SYN_ARGS);
    auto comma = pop(stack, SYN_COMMA);
    auto id = pop(stack, SYN_ID);
    auto type = pop(stack, SYN_TYPE);
    res.data = new ArgsSyntax(
        TOKEN_T(type)->getToken()->getVal(),
        TOKEN_T(id)->getToken()->getVal(), 
        ARGS_T(args));
    return res;
}
// /ARGS>/TYPE/ID
stackblk r2(deque<stackblk> &stack) {
    stackblk res;
    auto id = pop(stack, SYN_ID);
    auto type = pop(stack, SYN_TYPE);
    res.data = new ArgsSyntax(
        TOKEN_T(type)->getToken()->getVal(),
        TOKEN_T(id)->getToken()->getVal(), 
        NULL);
    return res;
}
// /LINES>/LINE/LINES
stackblk r3(deque<stackblk> &stack) {
    stackblk res;
    auto lines = pop(stack, SYN_LINES);
    auto line = pop(stack, SYN_LINE);
    res.data = new LinesSyntax(LINE_T(line), LINES_T(lines));
    return res;
}
// /LINES>/LINE
stackblk r4(deque<stackblk> &stack) {
    stackblk res;
    auto line = pop(stack, SYN_LINE);
    res.data = new LinesSyntax(LINE_T(line), NULL);
    return res;
}
// /BLOCK>/LPREN/LINES/RPREN
stackblk r5(deque<stackblk> &stack) {
    stackblk res;
    auto rpren = pop(stack, SYN_RPREN);
    auto lines = pop(stack, SYN_LINES);
    auto lpren = pop(stack, SYN_LPREN);
    res.data = new ExecBlockSyntax(LINES_T(lines));
    return res;
}
// /FUNC>/TYPE/ID/LBR/ARGS/RBR/BLOCK
stackblk r6(deque<stackblk> &stack) {
    stackblk res;
    auto block = pop(stack, SYN_BLOCK);
    auto rbr = pop(stack, SYN_RBR);
    auto args = pop(stack, SYN_ARGS);
    auto lbr = pop(stack, SYN_LBR);
    auto id = pop(stack, SYN_ID);
    auto type = pop(stack, SYN_TYPE);
    res.data = new FuncSyntax(
        TOKEN_T(type)->getToken()->getVal(), 
        TOKEN_T(id)->getToken()->getVal(),
        ARGS_T(args), 
        BLOCK_T(block));
    return res;
}
// /PROGRAM>/FUNC/PROGRAM
stackblk r7(deque<stackblk> &stack) {
    stackblk res;
    auto program = pop(stack, SYN_PROGRAM);
    auto func = pop(stack, SYN_FUNC);
    res.data = new ProgramSyntax(FUNC_T(func), PROGRAM_T(program));
    return res;
}
// /PROGRAM>/DECL/PROGRAM
stackblk r8(deque<stackblk> &stack) {
    stackblk res;
    auto program = pop(stack, SYN_PROGRAM);
    auto decl = pop(stack, SYN_DECL);
    res.data = new ProgramSyntax(DECL_T(decl), PROGRAM_T(program));
    return res;
}
// /DECL>/TYPE/ID/ENDL
stackblk r9(deque<stackblk> &stack) {
    stackblk res;
    auto endl = pop(stack, SYN_ENDL);
    auto id = pop(stack, SYN_ID);
    auto type = pop(stack, SYN_TYPE);
    res.data = new DeclSyntax(
        TOKEN_T(type)->getToken()->getVal(),
        TOKEN_T(id)->getToken()->getVal());
    return res;
}
// /DECL>/TYPE/ID/ASSIGN/IMM/ENDL
stackblk r10(deque<stackblk> &stack) {
    printf("r10 not finished\n");
    stackblk res;
    auto endl = pop(stack, SYN_ENDL);
    pop(stack);
    pop(stack);
    auto id = pop(stack, SYN_ID);
    auto type = pop(stack, SYN_TYPE);
    res.data = new DeclSyntax(
        TOKEN_T(type)->getToken()->getVal(), 
        TOKEN_T(id)->getToken()->getVal());
    return res;
}
// /DEF>/TYPE/ID/ASSIGN/EXP/ENDL
stackblk r11(deque<stackblk> &stack) {
    stackblk res;
    // auto endl = pop(stack, SYN_ENDL);
    // auto exp = pop(stack, SYN_EXP);
    // auto assign = pop(stack, SYN_ASSIGN);
    // auto id = pop(stack, SYN_ID);
    // auto type = pop(stack, SYN_TYPE);
    printf("r11 not finished\n");
    exit(-1);
    return res;
}
// /LINE>/DECL
stackblk r12(deque<stackblk> &stack) {
    stackblk res;
    auto decl = pop(stack, SYN_DECL);
    res.data = new LineSyntax(SYN_DECL, DECL_T(decl));
    return res;
}
// /LINE>/DEF
stackblk r13(deque<stackblk> &stack) {
    stackblk res;
    printf("r13 not finished");
    return res;
}
// /LINE>/ID/ASSIGN/EXP/ENDL
stackblk r14(deque<stackblk> &stack) {
    stackblk res;
    auto endl = pop(stack, SYN_ENDL);
    auto exp = pop(stack, SYN_EXP);
    auto assign = pop(stack, SYN_ASSIGN);
    auto id = pop(stack, SYN_ID);
    res.data = new LineSyntax(TOKEN_T(id)->getToken()->getVal(), EXP_T(exp));
    return res;
}
// /LINE>/EXP/ENDL
stackblk r15(deque<stackblk> &stack) {
    stackblk res;
    auto endl = pop(stack, SYN_ENDL);
    auto exp = pop(stack, SYN_EXP);
    res.data = new LineSyntax(SYN_EXP, EXP_T(exp));
    return res;
}
// /CALL>/ID/LBR/EXPS/RBR
stackblk r16(deque<stackblk> &stack) {
    stackblk res;
    auto rbr = pop(stack, SYN_RBR);
    auto exps = pop(stack, SYN_EXPS);
    auto lbr = pop(stack, SYN_LBR);
    auto id = pop(stack, SYN_ID);
    res.data = new CallSyntax(
        TOKEN_T(id)->getToken()->getVal(),
        EXPS_T(exps));
    return res;
}
// /EXPS>/EXP/COMMA/EXPS
stackblk r17(deque<stackblk> &stack) {
    stackblk res;
    auto exps = pop(stack, SYN_EXPS);
    auto comma = pop(stack, SYN_COMMA);
    auto exp = pop(stack, SYN_EXP);
    res.data = new ExpsSyntax(EXP_T(exp), EXPS_T(exps));
    return res;
}
// /EXPS>/EXP
stackblk r18(deque<stackblk> &stack) {
    stackblk res;
    auto exp = pop(stack, SYN_EXP);
    res.data = new ExpsSyntax(EXP_T(exp), NULL);
    return res;
}
// /EXP>/LBR/EXP/OP/EXP/RBR
stackblk r19(deque<stackblk> &stack) {
    stackblk res;
    auto rbr = pop(stack, SYN_RBR);
    auto rexp = pop(stack, SYN_EXP);
    auto op = pop(stack, SYN_OP);
    auto lexp = pop(stack, SYN_EXP);
    auto lnr = pop(stack, SYN_LBR);
    res.data = new ExpSyntax(EXP_T(lexp), TOKEN_T(op), EXP_T(rexp));
    return res;
}
// /EXP>/ID
stackblk r20(deque<stackblk> &stack) {
    stackblk res;
    auto id = pop(stack, SYN_ID);
    res.data = new ExpSyntax(TOKEN_T(id));
    return res;
}
// /EXP>/IMM
stackblk r21(deque<stackblk> &stack) {
    stackblk res;
    auto imm = pop(stack, SYN_IMM);
    res.data = new ExpSyntax(TOKEN_T(imm));
    return res;
}
// /EXP>/CALL
stackblk r22(deque<stackblk> &stack) {
    stackblk res;
    auto call = pop(stack, SYN_CALL);
    res.data = new ExpSyntax(CALL_T(call));
    return res;
}
// /PROGRAM>/DECL
stackblk r23(deque<stackblk> &stack) {
    stackblk res;
    auto decl = pop(stack, SYN_DECL);
    res.data = new ProgramSyntax(DECL_T(decl), NULL);
    return res;
}

// /PROGRAM>/FUNC
stackblk r24(deque<stackblk> &stack) {
    stackblk res;
    auto func = pop(stack, SYN_FUNC);
    res.data = new ProgramSyntax(FUNC_T(func), NULL);
    return res;
}

reduce_fun reduce[ARLANG_RULES] = {
    r0,
    r1,
    r2,
    r3,
    r4,
    r5,
    r6,
    r7,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15,
    r16,
    r17,
    r18,
    r19,
    r20,
    r21,
    r22,
    r23,
    r24
};