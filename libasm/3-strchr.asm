section .text
    global asm_strchr  ; Export function for linkage

asm_strchr:
    mov rax, rdi        ; Copy string pointer to RAX (return value if match found)
    mov dl, sil         ; Move the character to search into DL

.loop:
    mov cl, byte [rax]  ; Load current character from string
    cmp cl, dl          ; Compare with the target character
    je .found           ; If equal, return pointer to match
    test cl, cl         ; Check if we reached the null terminator
    je .not_found       ; If yes, return NULL
    inc rax             ; Move to the next character
    jmp .loop           ; Repeat loop

.found:
    ret                 ; Return pointer to found character

.not_found:
    xor rax, rax        ; Set return value to NULL
    ret
