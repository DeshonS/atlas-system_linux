section .text
global asm_strcmp

asm_strcmp:
    xor rax, rax
.next_char:
    mov al, [rdi]
    mov dl, [rsi]
    cmp al, dl
    jne .diff
    test al, al
    je .done
    inc rdi
    inc rsi
    jmp .next_char
.diff:
    sub al, dl
    movsx rax, al
.done:
    ret