extern printf
extern scanf
extern exit

global main

section .text

main:
  ; printf("Enter a string: ");
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

  ; reverse the string
  mov r14, string ; first character
  mov r15, string
  add r15, [stringSize] ; last character
  dec r15

  ; loop through the string
loopString:
  cmp r14, r15
  jge printResult

  ; swap the characters
  mov al, [r14]
  mov bl, [r15]
  mov [r14], bl
  mov [r15], al

  ; increment the pointers
  inc r14
  dec r15
  jmp loopString

printResult:
  ; printf("The reverse of the string is %s.\n", string);
  mov rdi, strResult
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
  strResult db "The reverse of the string is %s.", 0ah, 0dh, 0

  strFormat db "%s", 0
  sizeForamt db "%lli", 0


section .bss
  string resb 100
  stringSize resq 1
