section .text
    global asm_strstr

asm_strstr:
    mov rax, rdi
    mov rbx, rsi

    mov cl, byte [rbx]
    test cl, cl
    jz .return_haystack

.next_start:
    mov rdx, rax
    mov rcx, rbx

.loop:
    mov bl, byte [rcx]
    test bl, bl
    jz .found
    mov al, byte [rdx]
    test al, al
    jz .not_found
    cmp al, bl
    jne .continue_search
    inc rdx
    inc rcx
    jmp .loop

.continue_search:
    inc rax
    mov dl, byte [rax]
    test dl, dl
    jnz .next_start

.not_found:
    xor rax, rax
    ret

.found:
    ret

.return_haystack:
    mov rax, rdi
    ret
