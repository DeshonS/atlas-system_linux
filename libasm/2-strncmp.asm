section .text
    global asm_strncmp

asm_strncmp:
    test rdx, rdx
    jz .equal

.loop:
    mov al, [rdi]
    mov bl, [rsi]
    cmp al, bl
    jne .difference
    test al, al
    jz .equal
    inc rdi
    inc rsi
    dec rdx
    jnz .loop

.equal:
    xor eax, eax
    ret

.difference:
    movzx eax, al
    movzx ebx, bl
    sub eax, ebx
    ret
