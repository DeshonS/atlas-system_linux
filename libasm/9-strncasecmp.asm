section .text
    global asm_strncasecmp

asm_strncasecmp:
    test rdx, rdx
    je .done_zero

.loop:
    test rdx, rdx
    je .done_zero

    mov al, byte [rdi]
    mov dl, byte [rsi]

    cmp al, 'A'
    jl .skip1
    cmp al, 'Z'
    jg .skip1
    add al, 32

.skip1:
    cmp dl, 'A'
    jl .skip2
    cmp dl, 'Z'
    jg .skip2
    add dl, 32

.skip2:
    cmp al, dl
    jne .done

    test al, al
    je .done

    dec rdx
    inc rdi
    inc rsi
    jmp .loop

.done:
    sub al, dl
    movsx eax, al
    ret

.done_zero:
    xor eax, eax
    ret