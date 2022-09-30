; print positive integer
; 64bit x86-64 Intel Syntax

; [expression] means content of memory at address expression

; bss
; block starting symbol
; portion of object file that contains statically allocated variables
; variables that are declared but have not been assigned a value yet

section .bss
    buffer  resb 100  ; allocate 100 bytes
    pos     resb 8    ; allocate 8   bytes to store 64bit address    

    ; buffer: store string of characters
    ; pos: pointer to 8 bytes that store current position in buffer

       
    ;
    ;        pos            
    ;      +-----+        +-----+  
    ;      | 200 |        | 300 |  
    ;      +-----+        +-----+   
    ;        100            200
    ;
    ;       buffer
    ;      +------+------+------+------+ 
    ;      | '\n' |   4  |   2  |  3   |
    ;      +------+------+------+------+ 
    ;         300    364    428    492
    ;
    ;       output = 324
    ;
    ;       [pos] <- address of buffer
    ;

section .text
     global _printRAX
 

_printRAX:

    ; load memory address of buffer[0] into rcx
    mov rcx,   buffer

    ; load new line character into buffer[0]
    mov rbx,   0x0A     ; 0x0A is '\n'
    mov [rcx], rbx      ; buffer[0] = '\n'

    ; increment pos 
    inc rcx             ; x++
    mov [pos], rcx      ; *pos = &buffer[x]


; load digits into buffer
_load_buffer:
    
    ; div is always applied to edx:rax
    ;
    ; quotient  is stored in rax
    ; remainder is stored in rdx
    
    mov rdx, 0      ; 0:rax
    mov rbx, 10     ; temp = 10
    div rbx         ; 0:rax / temp
    
    push rax        ; save quotient    
 
    ; convert digit to ascii character and load into buffer
    add rdx, '0'    ; convert digit to ascii character
    mov rcx, [pos]  ; rcx = current buffer address
    mov [rcx], dl   ; load character

    ; increment pos
    inc rcx         ; x++
    mov [pos], rcx  ; *pos = &buffer[x]
    
    pop rax         ; restore quotient

    ; if remainder is greater then 0 repeat loop
    cmp rax, 0
    jne _load_buffer



; print digits from buffer
_print_buffer:

    mov rcx, [pos]  ; move pointer to character into rcx
    
    ; print character
    mov rax, 1      ; write syscall
    mov rdi, 1      ; 1st arg: use stdout as fp
    mov rsi, rcx    ; 2nd arg: use the character as the buffer
    mov rdx, 1      ; 3rd arg: buffer length
    syscall

    ; decrement buffer position
    ; pos = pointer to buffer pointer
    mov rcx, [pos]  ; x = *pos
    dec rcx         ; x--    
    mov [pos], rcx  ; *pos = &buffer[x]
 
    ; if *pos >= &buffer repeat loop 
    cmp rcx, buffer
    jge _print_buffer
 
    ret