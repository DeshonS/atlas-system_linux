section .text
global my_strcmp

my_strcmp:
    xor rax, rax           ; Set RAX (result) to 0
.next_char:
    mov al, [rdi]          ; Load byte from first string
    cmp al, [rsi]          ; Compare with second string
    jne .diff              ; If not equal, jump to diff
    test al, al            ; Check if we’ve hit \0
    je .done               ; If \0, strings are equal
    inc rdi                ; Advance pointers
    inc rsi
    jmp .next_char         ; Repeat
.diff:
    sub rax, [rsi]         ; Return difference
.done:
    ret