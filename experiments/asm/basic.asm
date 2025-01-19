bits 64

section .data ; initialized data
msg db "Hey, Actarus !", 0xa
string_length equ $ - msg

section .bss ; variables

section .text
    global _start ; entry point

_start:
    ; Write syscall
    mov rax, 1        ; syscall: sys_write (1)
    mov rdi, 1        ; file descriptor: stdout (1)
    mov rsi, msg      ; pointer to the message
    mov rdx, string_length ; message length
    syscall           ; make the system call

    ; Exit syscall
    mov rax, 60       ; syscall: sys_exit (60)
    xor rdi, rdi      ; status: 0
    syscall           ; make the system call
