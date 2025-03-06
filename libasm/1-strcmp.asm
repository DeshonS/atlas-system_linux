section .text
global asm_strcmp

asm_strcmp:
    xor rax, rax          ; Set RAX (result) to 0
.next_char:
    mov al, byte [rdi]    ; Load byte from first string (rdi points to the address of the first string)
    mov dl, byte [rsi]    ; Load byte from second string (rsi points to the address of the second string)
    cmp al, dl            ; Compare the two bytes
    jne .diff             ; If not equal, jump to the diff label
    test al, al           ; Check if we’ve hit '\0'
    je .done              ; If '\0', strings are equal (end of string)
    inc rdi               ; Increment the pointer to the first string
    inc rsi               ; Increment the pointer to the second string
    jmp .next_char        ; Repeat the comparison for the next characters
.diff:
    sub al, dl            ; Compute the difference between the two bytes
    mov rax, al         ; Sign-extend AL to RAX
.done:
    ret