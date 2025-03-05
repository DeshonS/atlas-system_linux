section .text
    global asm_strncasecmp

asm_strncasecmp:
.loop:
    test    rdx, rdx
    jz      .done

    mov     al, byte [rdi]
    mov     bl, byte [rsi]

    or      al, 0x20
    or      bl, 0x20

    cmp     al, bl
    jne     .not_equal

    test    al, al
    jz      .done

    inc     rdi
    inc     rsi
    dec     rdx
    jmp     .loop

.not_equal:
    sub     al, bl
    ret

.done:
    xor     eax, eax
    ret
