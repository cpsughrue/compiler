
section .text
    global main
    extern printf

main:
    
    push rbp            ; prologue  
    mov  rbp, rsp       ; prologue

    mov rdi, fmt
    mov rsi, -10
    mov rax, 0

    call printf wrt ..plt

    mov rsp, rbp        ; epilogue
    pop rbp             ; epilogue

    mov rax, 0
    ret

section .data
    ; db = define byte
    fmt: db "%d", 10, 0 ; printf fmt, "\n", '0'