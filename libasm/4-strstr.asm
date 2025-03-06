section .text
    global asm_strstr

asm_strstr:
    ; Arguments:
    ; rdi - haystack (string to search in)
    ; rsi - needle (substring to find)

    test rsi, rsi        ; Check if needle is NULL
    jz .return_haystack  ; If NULL, return haystack

    mov rax, rdi         ; Save haystack start in RAX

.next_start:
    mov rbx, rdi         ; Save current haystack position
    mov rcx, rsi         ; Reset needle position

.check:
    mov al, byte [rbx]   ; Load char from haystack
    mov dl, byte [rcx]   ; Load char from needle
    test dl, dl          ; Check if end of needle
    jz .found            ; If so, return pointer to match
    test al, al          ; Check if end of haystack
    jz .not_found        ; If so, return NULL
    cmp al, dl           ; Compare characters
    jne .next_haystack   ; If not equal, move to next haystack position

    inc rbx              ; Move to next char in haystack
    inc rcx              ; Move to next char in needle
    jmp .check           ; Continue checking

.next_haystack:
    inc rdi              ; Move haystack forward
    mov al, byte [rdi]   ; Load new character
    test al, al          ; Check if end of haystack
    jnz .next_start      ; If not, check new position

.not_found:
    xor rax, rax         ; Return NULL (no match found)
    ret

.found:
    mov rax, rdi         ; Set return value to match location
    ret

.return_haystack:
    mov rax, rdi         ; If needle is empty, return haystack
    ret
