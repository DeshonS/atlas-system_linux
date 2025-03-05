section .bss
    buffer resb 1

section .text
    global asm_putc

asm_putc:
    mov byte [buffer], dil
    mov rax, 1
    mov rdi, 1
    mov rsi, buffer
    mov rdx, 1
    syscall
    ret