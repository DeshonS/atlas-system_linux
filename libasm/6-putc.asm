section .text
    global asm_putc

asm_putc:
    sub     rsp, 8
    mov     byte [rsp], dil

    mov     eax, 1
    mov     edi, 1
    mov     rsi, rsp
    mov     edx, 1
    syscall

    add     rsp, 8
    mov     eax, 1
    ret
