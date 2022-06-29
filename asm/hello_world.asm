; hello_world
; x86-64 Intel Syntax

global _start

; program insturctions
section .text:

_start:
; write - write to a file descriptor (fd)
; ssize_t write(int fd, const void *buf, size_t count);
;
;       ebx fd   - file descriptor
;       ecx buf  - buffer (i.e. output)
;       edx cout - number of bytes in buffer  

    ; write syscall
    mov eax, 0x4            ; 0x4 system call number (sys_write)

    mov ebx, 1              ; 1st arg: use stdout as the fd    
    mov ecx, message        ; 2nd arg: use the message as the buffer
    mov edx, message_len    ; 3rd arg: buffer length
    
    int 0x80                ; call kernal

    ; exit syscall
    mov eax, 0x1            ; 0x1 system call number (sys_exit)
    mov ebx, 0x0            ; 1st arg: exit code
    int 0x80                ; call kernal



; define variables
section .data:
    
    ; "db" define bytes 
    message: db "hello world", 0xA  ; "0xA" new line character 
    message_len equ $-message       ; length of variable

    ; $ current address - address of message = length of message
