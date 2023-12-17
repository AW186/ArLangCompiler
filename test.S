    global main
    section .text
main:
    push rbx
    push r12
    push r13
    push r14
    push r15
    push rbp
    mov rbp, rsp
    sub rsp, 8

    sub rsp, 8


    mov rax, [rbp-8]

    mov rax, [rbp-8]


    mov rax, 1

    add rax, 0
    jnz if0
if0:
    push rax
    push rcx
    push rdx
    push rsi
    push rdi
    push r8
    push r9
    push r10
    push r11

    mov rax, 12

    push rax

    mov rax, imm0

    push rax

    mov rax, 1

    push rax

    mov rax, 1

    push rax
    pop rax
    pop rdi
    pop rsi
    pop rdx
syscall
    pop r11
    pop r10
    pop r9
    pop r8
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rax

endif0:



    mov rsp, rbp
    pop rbp
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    ret


    section .data
imm0: db "hello world!"


