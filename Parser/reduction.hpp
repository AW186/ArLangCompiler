#ifndef REDUCTION_HPP
#define REDUCTION_HPP

#include <deque>
#include "syntax.hpp"

typedef struct stackblk {
    int type;
    int state;
    union {
        FileSyntax          *file;
        LineSyntax          *line;
        LinesSyntax         *lines;
        ProgramSyntax       *program;
        ExpSyntax           *exp;
        ExecBlockSyntax     *block;
        FuncSyntax          *func;
        Token               *token;
    } u;
} stackblk;

typedef auto (*reduce_fun)(deque<stackblk> &) -> stackblk;

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
*/

#define ARLANG_RULES 22

stackblk r0(deque<stackblk> &stack);
stackblk r1(deque<stackblk> &stack);
stackblk r2(deque<stackblk> &stack);
stackblk r3(deque<stackblk> &stack);
stackblk r4(deque<stackblk> &stack);
stackblk r5(deque<stackblk> &stack);
stackblk r6(deque<stackblk> &stack);
stackblk r7(deque<stackblk> &stack);
stackblk r8(deque<stackblk> &stack);
stackblk r9(deque<stackblk> &stack);
stackblk r10(deque<stackblk> &stack);
stackblk r11(deque<stackblk> &stack);
stackblk r12(deque<stackblk> &stack);
stackblk r13(deque<stackblk> &stack);
stackblk r14(deque<stackblk> &stack);
stackblk r15(deque<stackblk> &stack);
stackblk r16(deque<stackblk> &stack);
stackblk r17(deque<stackblk> &stack);
stackblk r18(deque<stackblk> &stack);
stackblk r19(deque<stackblk> &stack);
stackblk r20(deque<stackblk> &stack);
stackblk r21(deque<stackblk> &stack);

reduce_fun reduce[ARLANG_RULES] = {
    r0,
    r1,
    // r2,
    // r3,
    // r4,
    // r5,
    // r6,
    // r7,
    // r8,
    // r9,
    // r10,
    // r11,
    // r12,
    // r13,
    // r14,
    // r15,
    // r16,
    // r17,
    // r18,
    // r19,
    // r20,
    // r21
};

#endif