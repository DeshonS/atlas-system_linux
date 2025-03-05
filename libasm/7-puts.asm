section .text
    global asm_puts
    extern asm_strlen

asm_puts:
    mov     rdi, rdi
    call    asm_strlen
    
    mov     rax, 1
    mov     rdi, 1
    mov     rsi, rdi
    mov     rdx, rax
    syscall
    
    ret