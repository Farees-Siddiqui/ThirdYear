extern printf
extern scanf

global main

section .text 

main:
  ; printf("What is your cat's name? ");
  mov rdi, namePrompt
  mov rax, 0
  push r8
  call printf 
  pop r8

  ; scanf("%s", name);
  mov rdi, nameFormat 
  mov rsi, name 
  mov rax, 0
  push r9  ; this can be any 64-bit register
  call scanf 
  pop r9

  ; printf("What is your cat's age? ");
  mov rdi, agePrompt
  mov rax, 0
  push r9 
  call printf 
  pop r9

  ; scanf("%d", &age);
  mov rdi, ageFormat
  mov rsi, age 
  mov rax, 0
  push r9 
  call scanf 
  pop r9

  ; printf("Your cat, %s, is %d years old.\n", name, age);
  mov rdi, responseFormat
  mov rsi, name 
  mov rdx, [age]
  mov rax, 0
  push r9 
  call printf 
  pop r9

  ; exit the program
  ret

section .data
  namePrompt db "What is your cat's name? ", 0
  nameFormat db "%s", 0
  ;name db "                    ", 0

  agePrompt db "What is your cat's age? ", 0
  ageFormat db "%d", 0

  responseFormat db "Your cat, %s, is %d years old.", 0ah, 0dh, 0

section .bss 
  name resb 51
  age resq 1