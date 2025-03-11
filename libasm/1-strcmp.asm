section .text
    global asm_strcmp

asm_strcmp:
.loop:
    mov al, byte [rdi]
    mov dl, byte [rsi]
    cmp al, dl
    jne .done
    test al, al
    je .done
    inc rdi
    inc rsi
    jmp .loop

.done:
    sub al, dl
    movsx eax, al
    ret