extern printf
extern scanf
extern exit

global main

section .text

main:
  mov rdi, strPrompt
  mov rax, 0
  push rbx
  call printf
  pop rbx

  ; scanf("%s", string);
  mov rdi, strFormat
  mov rsi, string
  mov rax, 0
  push rbx
  call scanf
  pop rbx

  ; printf("What is the length of the string? ");
  mov rdi, strSizePrompt
  mov rax, 0
  push rbx
  call printf
  pop rbx

  ; scanf("%lli", stringSize);
  mov rdi, sizeForamt
  mov rsi, stringSize
  mov rax, 0
  push rbx
  call scanf
  pop rbx

  mov r14, string
  mov r15, string
  add r15, [stringSize]
  dec r15

; check if the string is a palindrome
checkPalindrome:
  cmp r14, r15
  jge palindrome

  mov al, [r14]
  mov bl, [r15]

  ; compare if the characters are the same
  cmp al, bl
  jne notPalindrome

  inc r14
  dec r15
  jmp checkPalindrome


palindrome:
  ; printf("The string %s is a palindrome.\n", string);
  mov rdi, success
  mov rsi, string
  mov rax, 0
  push rbx
  call printf
  pop rbx

  jmp endProgram

notPalindrome:
  ; printf("The string %s is not a palindrome.\n", string);
  mov rdi, fail
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
  strPrompt db "Enter a string: ", 0
  strSizePrompt db "What is the length of the string? ", 0

  success db "The string %s is a palindrome.", 0ah, 0dh, 0
  fail db "The string %s is a not palindrome.", 0ah, 0dh, 0

  strFormat db "%s", 0
  sizeForamt db "%lli", 0

section .bss
  string resb 100
  stringSize resq 1
