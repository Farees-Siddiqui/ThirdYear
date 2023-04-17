extern printf
extern scanf

global main

section .text

copyDivisible: 
    ; rdi = destination array
    ; rsi = source array
    ; rdx = size of source array
    ; rcx = divisor
    
    mov r15, [rsi]
    mov r14, rdx

    mov rdx, 0
    mov rax, r15
    mov rbx, [rcx]
    idiv rbx

    cmp rdx, 0
    jne skip

    mov rdi, outputDisplayFormat
    mov rsi, r15 
    mov rdx, [rcx]
    push rbx
    call printf
    pop rbx

    mov [rdi], r15
    inc rdi
    jmp copyDivisible

skip:
    add rsi, 8
    dec r14
    cmp r14, 0
    jne copyDivisible

    ret

main:
    mov rdi, getNumPrompt
    mov rax, 0
    push rbx
    call printf
    pop rbx

    mov rdi, getNumFormat
    mov rsi, divisor
    mov rax, 0
    push rbx
    call scanf
    pop rbx

    mov rdi, destinationArray
    mov rsi, startArray
    mov rdx, 20
    mov rcx, divisor
    push rbx
    call copyDivisible
    pop rbx

	

section .data

	startArray dq 15, 23, 19, -28, 13, 6, 11, -72, 30, -9, 21, -2, 33, -5, 70, -1, -16, 0, -7, 3
	

	getNumPrompt db "Enter a number: ", 0
	getNumFormat db "%d", 0
	divisor dq 0

    outputDisplayFormat db "%d is divisible by %d", 0ah, 0dh, 0

section .bss
    destinationArray resq 20
