extern printf
extern scanf

global main

section .text 

main:

  ; printf("Enter your age: ");
  mov rdi, agePrompt 
  mov rax, 0
  push rcx
  call printf
  pop rcx

  ; scanf("%d", &age);
  mov rdi, ageFormat 
  mov rsi, age
  mov rax, 0
  push rcx 
  call scanf
  pop rcx

  ; age += 5;
  mov rbx, [age]
  add rbx, 5

  ; printf("In 5 years, you will be %d years old.\n", age);
  mov rdi, responseFormat
  mov rsi, rbx
  mov rax, 0
  push rcx
  call printf
  pop rcx

  ; exit the program
  ret

section .data

  agePrompt db "Enter your age: ", 0
  ageFormat db "%d", 0
  age dq 0

  responseFormat db "In 5 years, you will be %d years old.", 0ah, 0dh, 0
