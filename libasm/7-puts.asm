section .text
    global asm_puts
    extern asm_strlen

asm_puts:
    mov     rdi, rdi
    call    asm_strlen
    
    mov     rdx, rax
    mov     rax, 1
    mov     rdi, 1
    mov     rsi, rdi
    syscall
    
    mov     rax, rdx
    ret