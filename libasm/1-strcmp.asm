section .text
    global asm_strcmp

asm_strcmp:
    xor rax, rax

.loop:
    movzx rax, byte [rdi]
    movzx rdx, byte [rsi]
    cmp al, dl
    jne .done
    test al, al
    je .done
    inc rdi
    inc rsi
    jmp .loop

.done:
    sub eax, edx
    ret
