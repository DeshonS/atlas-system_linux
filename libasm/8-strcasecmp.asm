section .text
    global asm_strcasecmp

asm_strcasecmp:
    .loop:
        movzx edx, byte [edi]
        movzx ecx, byte [esi]
        or     edx, 0x20
        or     ecx, 0x20
        cmp    edx, ecx
        jne    .not_equal
        test   edx, edx
        jz     .equal
        inc    edi
        inc    esi
        jmp    .loop

    .not_equal:
        sub    eax, eax
        mov    al, dl
        sub    al, cl
        ret

    .equal:
        xor    eax, eax
        ret
