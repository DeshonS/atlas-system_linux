section .text
    global asm_strpbrk

asm_strpbrk:
    xor rax, rax  

.loop:
    mov cl, byte [rdi]  
    test cl, cl         
    jz .done            

    mov rbx, rsi        

.next_char:
    mov dl, byte [rbx]  
    test dl, dl         
    jz .continue_search 
    cmp cl, dl          
    je .found           

    inc rbx             
    jmp .next_char      

.continue_search:
    inc rdi             
    jmp .loop           

.found:
    mov rax, rdi        
.done:
    ret  