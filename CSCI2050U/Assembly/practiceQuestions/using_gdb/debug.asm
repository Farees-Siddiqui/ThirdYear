extern printf
global main

section .text
main:
	mov	rdi, format     ; argument #1
	mov	rsi, message    ; argument #2
	mov	rax, 0
  	call printf		; call printf

	mov rax, 0
	ret                     ; return 0

section .data
	message:    db "Hello, world!", 0
	format:     db "%s", 0xa, 0
	courseCode: dq 2050
