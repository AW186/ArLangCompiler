
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
*/

#define ARLANG_RULES 22

stackblk pop(deque<stackblk> &stack) {
    stackblk res = stack.back();
    stack.pop_back();
    return res;
}

stackblk pop(deque<stackblk> &stack, int type) {
    stackblk res = pop(stack);
    if (res.type != type) {
        printf("TYPE ERROR\n");
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
stackblk r1(deque<stackblk> &stack);
// /ARGS>/TYPE/ID
stackblk r2(deque<stackblk> &stack);
// /LINES>/LINE/LINES
stackblk r3(deque<stackblk> &stack) {
    stackblk res;
    auto lines = pop(stack, SYN_LINES).u.lines;
    auto line = pop(stack, SYN_LINE).u.line;
    res.u.lines = new LinesSyntax(line, lines);
    res.type = SYN_LINES:
    return res;
}
// /LINES>/LINE
stackblk r4(deque<stackblk> &stack) {
    stackblk res;
    auto line = pop(stack, SYN_LINE).u.line;
    res.u.lines = new LinesSyntax(line, NULL);
    res.type = SYN_LINES;
    return res;
}
// /BLOCK>/LPREN/LINES/RPREN
stackblk r5(deque<stackblk> &stack) {
    stackblk res;
    auto rpren = pop(stack, SYN_RPREN);
    auto lines = pop(stack)
}
// stackblk r6(deque<stackblk> &stack);
// stackblk r7(deque<stackblk> &stack);
// stackblk r8(deque<stackblk> &stack);
// stackblk r9(deque<stackblk> &stack);
// stackblk r10(deque<stackblk> &stack);
// stackblk r11(deque<stackblk> &stack);
// stackblk r12(deque<stackblk> &stack);
// stackblk r13(deque<stackblk> &stack);
// stackblk r14(deque<stackblk> &stack);
// stackblk r15(deque<stackblk> &stack);
// stackblk r16(deque<stackblk> &stack);
// stackblk r17(deque<stackblk> &stack);
// stackblk r18(deque<stackblk> &stack);
// stackblk r19(deque<stackblk> &stack);
// stackblk r20(deque<stackblk> &stack);
// stackblk r21(deque<stackblk> &stack);