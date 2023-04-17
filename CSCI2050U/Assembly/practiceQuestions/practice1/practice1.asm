extern printf
extern scanf

global main

section .text

main:
  ; printf("Enter a number: ");
  mov rdi, numberPrompt
  mov rax, 0
  push rbx
  call printf
  pop rbx

  ; scanf("%lli", &toFind);
  mov rdi, numberFormat
  mov rsi, toFind
  mov rax, 0
  push rbx
  call scanf
  pop rbx
  
  ; search the list
  mov r12, list
  mov r13, [listSize]
  mov rbx, [toFind]
  mov r14, [toFind]
loopList:
  mov r15, [r12] ; first element of the list
  cmp r15, rbx

  je numberFound

  add r12, 8 ; move to the next element
  dec r13
  cmp r13, 0
  jne loopList


numberNotFound:
  ; printf("The number %lli was not found in the list.\n", toFind);
  mov rdi, outNotFound
  mov rsi, [toFind]
  mov rax, 0
  push rbx
  call printf
  pop rbx
  jmp endProgram

numberFound:
  ; printf("The number %lli was found in the list.\n", toFind);
  mov rdi, outputFormat
  mov rsi, [toFind]
  mov rax, 0
  push rbx
  call printf
  pop rbx
  

endProgram:
  ; exit
  mov rax, 0
  ret

section .data
  list dq -4, 7, 6, 11, -1, 0, 3, 9, 16, -3
  listSize dq 10
  numberPrompt db "Enter a number: ", 0
  numberFormat db "%lli", 0
  outputFormat db "The number %lli was found in the list", 0ah, 0dh, 0
  outNotFound db "The number %lli was not found in the list.", 0ah, 0dh, 0

section .bss
  toFind resq 1
