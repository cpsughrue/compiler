section .text
    global _program:

_program:

    ; 3 + 2

    push    3
    push    2
    pop     r10
    pop     r11
    add     r11, r10 

    mov rax, r11
    ret