bits 64
section .text
global asm_strcmp

asm_strcmp:
    xor rax, rax
.next_char:
    movzx rax, byte [rdi]
    movzx rdx, byte [rsi]
    cmp rax, rdx
    jne .diff
    test rax, rax
    je .done
    inc rdi
    inc rsi
    jmp .next_char
.diff:
    sub rax, rdx
.done:
    ret