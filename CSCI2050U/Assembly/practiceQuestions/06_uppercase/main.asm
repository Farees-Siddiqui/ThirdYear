extern printf
extern scanf

global main

section .text

main:

  ; printf("Enter a message: ");
  mov rdi, messagePrompt
  mov rax, 0
  push r10 ; this could be any 64-bit register
  call printf
  pop r10

  ; scanf("%s", message);
  mov rdi, messageFormat
  mov rsi, message
  mov rax, 0
  push r10
  call scanf
  pop r10 

  ; convert the string to uppercase
  mov rsi, message 

nextChar:

  ; load the next character
  mov al, [rsi]

  ; check to see if we've reached the end of the string
  ; exit if the character is null (0)
  cmp al, 0
  je printResult

  ; check to see if the character is before 'a'
  cmp al, 97 ; 'a'
  jl skipChar

  ; check to see if the character is after 'z'
  cmp al, 122 ; 'z'
  jg skipChar

  ; convert this character to uppercase (subtract 32)
  sub al, 32
  mov [rsi], al

skipChar:
  ; go to the next character
  inc rsi ; add rsi, 1
  jmp nextChar

printResult:
  ; printf("The string converted to uppercase is '%s'.\n", message);
  mov rdi, resultFormat 
  mov rsi, message 
  mov rax, 0
  push r10 
  call printf 
  pop r10

  ; exit the program
  mov rax, 0
  ret

section .data
  messagePrompt db "Enter a message: ", 0
  messageFormat db "%s", 0

  resultFormat db "The string converted to uppercase is '%s'.", 0ah, 0dh, 0

section .bss
  message resb 25