bits 64
section .text
global asm_strcmp

asm_strcmp:
    xor rax, rax
.next_char:
    mov al, byte [rdi]
    mov dl, byte [rsi]
    cmp al, dl
    jne .diff
    test al, al
    je .done
    inc rdi
    inc rsi
    jmp .next_char
.diff:
    movsx rax, al
    movsx rdx, dl
    sub rax, rdx
.done:
    ret
