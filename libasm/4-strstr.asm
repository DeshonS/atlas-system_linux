section .text
    global asm_strstr

asm_strstr:
    mov rax, rdi           
    test rsi, rsi          
    jz .return_haystack    

    mov cl, byte [rsi]     
    test cl, cl            
    jz .return_haystack    

.next_start:
    mov rdx, rax           
    mov rcx, rsi           

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
    mov rax, rdi
    add rax, rdi           
    sub rax, rdx           
    ret                    

.return_haystack:
    mov rax, rdi           
    ret