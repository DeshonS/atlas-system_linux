section .text
    global asm_strcasecmp

asm_strcasecmp:
    test    rdi, rdi
    jz      .null_pointer

    test    rsi, rsi
    jz      .null_pointer

    .loop:
        mov   rdx, byte [rdi]
        mov   rcx, byte [rsi]
        or      rdx, 0x20
        or      rcx, 0x20
        cmp     rdx, rcx
        jne     .not_equal

        test    rdx, rdx
        jz      .equal

        inc     rdi
        inc     rsi
        jmp     .loop

    .not_equal:
        sub     rax, rax
        mov     al, dl
        sub     al, cl
        ret

    .equal:
        xor     rax, rax
        ret

    .null_pointer:
        xor     rax, rax
        ret
