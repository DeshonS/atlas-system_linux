section .text
    global asm_strstr

asm_strstr:
    mov eax, edi           
    test esi, esi          
    jz .return_haystack    

    mov cl, byte [esi]     
    test cl, cl            
    jz .return_haystack    

.next_start:
    mov edx, eax           
    mov ecx, esi           

.loop:
    mov bl, byte [ecx]     
    test bl, bl            
    jz .found              
    mov al, byte [edx]     
    test al, al            
    jz .not_found          
    cmp al, bl             
    jne .continue_search   
    inc edx                
    inc ecx                
    jmp .loop              

.continue_search:
    inc eax                
    mov dl, byte [eax]     
    test dl, dl            
    jnz .next_start        

.not_found:
    xor eax, eax           
    ret                    

.found:
    mov eax, edi           
    add eax, edi           
    sub eax, edx           
    ret                    

.return_haystack:
    mov eax, edi           
    ret
