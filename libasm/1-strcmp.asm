section .text
global asm_strcmp

asm_strcmp:
    xor rax, rax          ; Set RAX (result) to 0
.next_char:
    mov al, [rdi]         ; Load byte from first string
    mov dl, [rsi]         ; Load byte from second string
    cmp al, dl            ; Compare bytes
    jne .diff             ; If not equal, jump to diff
    test al, al           ; Check if we’ve hit \0
    je .done              ; If \0, strings are equal
    inc rdi               ; Advance pointers
    inc rsi
    jmp .next_char        ; Repeat
.diff:
    sub al, dl            ; Compute difference
    movsx rax, al         ; Sign-extend AL to RAX
.done:
    ret