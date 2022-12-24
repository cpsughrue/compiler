
section .text
    global main
    extern printf

main:
    
    push rbp            ; prologue  
    mov  rbp, rsp       ; prologue

    mov rdi, fmt
    mov rsi, message
    mov rax, 0

    call printf wrt ..plt

    mov rsp, rbp        ; epilogue
    pop rbp             ; epilogue

    mov rax, 0
    ret

section .data
    ; db = define byte
    message: db "Hello world", 10, 0
    fmt: db "%s", 10, 0


