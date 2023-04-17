; Print hello world

extern printf; 
extern exit;

global main

section .text

main:
    mov rdi, msg
    mov rax, 0
    push rbx
    call printf
    pop rbx

    mov rax, 0
    call exit

section .data
    msg db "Hello, world!", 0ah, 0dh, 0