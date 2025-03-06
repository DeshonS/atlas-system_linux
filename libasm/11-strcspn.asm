section .text
    global asm_strcspn

asm_strcspn:
    xor rax, rax

.loop:
    mov al, byte [rdi + rax]
    test al, al
    jz .done

    mov rbx, rsi
.next_char:
    mov dl, byte [rbx]
    test dl, dl
    jz .continue_search
    cmp al, dl
    je .done

    inc rbx
    jmp .next_char

.continue_search:
    inc rax
    jmp .loop

.done:
    ret