extern printf
extern scanf
extern exit

global main

section .text

main:
  ; printf("Enter a string: ");
  mov rdi, stringPrompt
  mov rax, 0
  push rbx
  call printf
  pop rbx

  ; scanf("%s", string);
  mov rdi, stringFormat
  mov rsi, string
  mov rax, 0
  push rbx
  call scanf
  pop rbx

  ; printf("What is the length of the string? ");
  mov rdi, stringSizePrompt
  mov rax, 0
  push rbx
  call printf
  pop rbx

  ; scanf("%lli", stringSize);
  mov rdi, stringSizeFormat
  mov rsi, stringSize
  mov rax, 0
  push rbx
  call scanf
  pop rbx

  ; reverse the string
  mov r14, string 
  mov r15, string 
  add r15, [stringSize]
  dec r15

nextChar:
  ; check if we are done 
  cmp r14, r15 
  jge printResult 

  ; swap these two characters
  mov al, [r14]
  mov bl, [r15]
  mov [r14], bl 
  mov [r15], al

  ; move to the next characters
  dec r15 
  inc r14 
  jmp nextChar


printResult:
  ; printf("The reverse of the string is %s.\n", string);
  mov rdi, responseFormat
  mov rsi, string
  mov rax, 0
  push rbx
  call printf
  pop rbx

endProgram:
  ; exit
  mov rax, 0
  ret

section .data
  stringPrompt db "Enter a string: ", 0
  stringFormat db "%s", 0

  stringSizePrompt db "What is the length of the string? ", 0
  stringSizeFormat db "%lli", 0

  responseFormat db "The reverse of the string is %s.", 0ah, 0dh, 0

section .bss 
  string resb 50
  stringSize resq 1
