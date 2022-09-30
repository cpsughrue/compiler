section .text
    global _start
    extern _printRAX


; print negative sign
_print_negative:

    push 0x2D       ; '-'
    
    mov rax, 1      ; write syscall
    mov rdi, 1      ; 1st arg: use stdout as fp
    mov rsi, rsp    ; 2nd arg: use the character as the buffer
    mov rdx, 1      ; 3rd arg: buffer length
    syscall

    add rsp, 8      ; reset stack pointer (8 bytes = 64 bits)

    ret


_start:
    
    mov  rax, -4     

    cmp  rax, 0
    jl   negative ; if negative print '-'
    jmp  print    ; else (positive or 0) print integer

    negative:
        imul rax, -1
        push rax
        call _print_negative
        pop  rax

    print:
        call _printRAX

    mov rax, 60
    mov rdi, 0
    syscall