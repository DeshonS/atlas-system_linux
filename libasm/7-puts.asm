section .text
    global asm_puts
    extern asm_strlen

asm_puts:
    mov     rsi, rdi
    call    asm_strlen
    mov     rdx, rax
    mov     rax, 1
    mov     rdi, 1
    syscall
    mov     rax, rdx
    ret
