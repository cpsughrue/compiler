section .text
    global _program:

_program:

    ; 4 ^ 2

    push    4
    push    2

    pop     r10     ; exponent
    pop     r11     ; base

    cmp     r10, 0
    jne     pow

    ; if exponent is 0 then move 1 into rax and return
    mov     rax, 1
    jmp     pow_end
    
    ; move base into rax and use r12 as accumulator
    pow:
        
        mov     rax, r11
        mov     r12, 1

    pow_loop:

        cmp  r12, r10
        je pow_end

        inc  r12
        imul r11

        jmp   pow_loop

    pow_end:

        mov  r11, rax
        push r11

    pop     r11
    mov     rax, r11
    ret