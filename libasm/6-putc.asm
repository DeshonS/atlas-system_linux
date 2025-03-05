section .text
    global asm_putc

asm_putc:
    mov rax, 1
    mov rdi, 1
    mov rsi, rsp
    mov [rsp], dil
    mov rdx, 1
    syscall
    ret