section .text
    global asm_strspn

asm_strspn:
    xor rax, rax

.loop:
    mov al, byte [rdi + rax]
    test al, al
    jz .done

    mov rbx, rsi
.next_char:
    mov dl, byte [rbx]
    test dl, dl
    jz .done
    cmp al, dl
    je .continue_search

    inc rbx
    jmp .next_char

.continue_search:
    inc rax
    jmp .loop

.done:
    ret
