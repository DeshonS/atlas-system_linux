section .text
    global asm_strcspn

asm_strcspn:
    xor rcx, rcx

.loop_s: 
    mov al, [rdi + rcx]
    test al, al
    je .done

    mov rbx, rsi

.loop_reject:
    mov dl, [rbx]
    test dl, dl
    je .done

    cmp al, dl
    je .done

    inc rbx
    jmp .loop_reject

    inc rcx
    jmp .loop_s

.done:
    mov rax, rcx
    ret