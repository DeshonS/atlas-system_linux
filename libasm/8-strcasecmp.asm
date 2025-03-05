section .text
    global asm_strcasecmp

asm_strcasecmp:
.loop:
    mov     al, byte [rdi]      ; Load byte from s1
    mov     bl, byte [rsi]      ; Load byte from s2

    or      al, 0x20            ; Convert s1 character to lowercase
    or      bl, 0x20            ; Convert s2 character to lowercase

    cmp     al, bl              ; Compare the lowercase characters
    jne     .not_equal          ; If not equal, jump to not_equal

    test    al, al              ; Test if the character is null (end of string)
    jz      .done               ; If both strings are done, we're done

    inc     rdi                 ; Move to next character in s1
    inc     rsi                 ; Move to next character in s2
    jmp     .loop               ; Repeat the loop

.not_equal:
    sub     al, bl              ; Return a difference (al - bl)
    ret

.done:
    xor     eax, eax            ; Return 0 if both strings are equal
    ret