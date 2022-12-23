
section .text
    global main
    extern printf

main:
    
    push rbp            ; prologue  
    mov  rbp, rsp       ; prologue

    mov  rdi,  fmt
    movq xmm0, 1.6
    mov  rax,  1

    call printf wrt ..plt

    mov rsp, rbp        ; epilogue
    pop rbp             ; epilogue

    mov rax, 0
    ret

section .data
    ; db = define byte
    fmt: db "%f", 10, 0 ; printf fmt, "\n", '0'