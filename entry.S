    global _start
    extern main
    section .text
_start:
    call main
    mov rax, 60                 ; system call for exit
    xor rdi, rdi                ; exit code 0
    syscall                           ; invoke operating system to exit
