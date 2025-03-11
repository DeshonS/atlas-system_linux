section .text
    global asm_strspn

asm_strspn:
    xor rcx, rcx

.loop_s:
    mov al, [rdi + rcx]
    test al, al
    je .done

    mov rbx, rsi

.loop_accept:
    mov dl, [rbx]
    test dl, dl
    je .done

    cmp al, dl
    je .match

    inc rbx
    jmp .loop_accept

.match:
    inc rcx
    jmp .loop_s

.done:
    mov rax, rcx
    ret