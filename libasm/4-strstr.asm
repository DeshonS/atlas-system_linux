section .text
    global asm_strstr

asm_strstr:
    test rsi, rsi          
    jz .return_haystack    

    movzx ecx, byte [rsi]  
    test cl, cl            
    jz .return_haystack    

    mov rax, rdi           

.next_start:
    mov rdx, rax           
    mov r8, rsi            

.loop:
    movzx r9b, byte [r8]   
    test r9b, r9b          
    jz .found              
    movzx r10b, byte [rdx] 
    test r10b, r10b        
    jz .not_found          
    cmp r10b, r9b          
    jne .continue_search   
    inc rdx                
    inc r8                 
    jmp .loop              

.continue_search:
    inc rax                
    movzx r11b, byte [rax] 
    test r11b, r11b        
    jnz .next_start        

.not_found:
    xor rax, rax           
    ret                    

.found:
    ret                    

.return_haystack:
    mov rax, rdi           
    ret