extern printf
extern scanf

global main

section .text 

main:
  ; printf("Enter a number: ");
  mov rdi, numberPrompt
  mov rax, 0
  push rax ; this can be any 64-bit register!
  call printf
  pop rax

  ; scanf("%d", &number);
  mov rdi, numberFormat
  mov rsi, number
  mov rax, 0
  push rax 
  call scanf 
  pop rax

  ; if (number % 2 == 0) {
  mov rdx, 0
  mov rax, [number]
  mov rbx, 2
  idiv rbx 

  cmp rdx, 0
  jne oddNumber

evenNumber:
  ; printf("The number %d is an even number.\n", number);
  mov rdi, evenNumberResponse
  mov rsi, [number]
  mov rax, 0
  push rax 
  call printf 
  pop rax

  ; } else {
  jmp exitProgram

oddNumber:
  ; printf("The number %d is an odd number.\n", number);
  mov rdi, oddNumberResponse
  mov rsi, [number]
  mov rax, 0
  push rax 
  call printf 
  pop rax

exitProgram:
  ret

section .data
  numberPrompt db "Enter a number: ", 0
  numberFormat db "%d", 0

  evenNumberResponse db "The number %d is an even number.", 0ah, 0dh, 0
  oddNumberResponse db "The number %d is an odd number.", 0ah, 0dh, 0

section .bss 
  number resq 1
  