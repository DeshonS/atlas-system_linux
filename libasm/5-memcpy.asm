section .text
    global asm_memcpy

asm_memcpy:
    test rdx, rdx
    je .done

    mov rax, rdi

.copy_loop:
    cmp rdx, 0
    je .done
    mov bl, [rsi]
    mov [rdi], bl
    inc rsi
    inc rdi
    dec rdx
    jmp .copy_loop

.done:
    ret
