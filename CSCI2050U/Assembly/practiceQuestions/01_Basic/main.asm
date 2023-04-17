extern printf
extern exit

global main

section .text

main:
  ; printf("Hello, world!\n");
  mov rdi, message
  mov rax, 0
  push rbx
  call printf
  pop rbx

  ; exit(0)
  mov rax, 0
  call exit

section .data
  message db "Hello, world!", 0ah, 0dh, 0
