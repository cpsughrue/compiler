section .text
    global _program:

_program:

    ; 3 + ( 2 - 6)

    push    3
    push    2
    push    6

    pop     r10
    pop     r11
    sub     r11, r10
    push    r11

    pop     r10
    pop     r11
    add     r11, r10
    push    r11

    pop     r11
    mov     rax, r11
    ret