section .text
    global _start
    extern _printRAX

_start:
    
    mov rax, 256
    call _printRAX

    mov rax, 60
    mov rdi, 0
    syscall