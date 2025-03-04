section .text
    global asm_strcmp;

asm_strcmp:
    xor rax, rax;
.loop
    mov al, [rdi]      
    mov dl, [rsi]      
    cmp al, dl         
    jne .done          
    test al, al        
    je .done           
    inc rdi            
    inc rsi            
    jmp .loop          

.done:
    sub eax, edx       
    ret