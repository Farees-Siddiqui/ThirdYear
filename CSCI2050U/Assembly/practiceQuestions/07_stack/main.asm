extern printf
extern scanf

global main 

section .text 

add5:

  mov rax, [rsp + 8]  ; 1
  add rax, [rsp + 16] ; 2
  add rax, [rsp + 24] ; 3
  add rax, [rsp + 32] ; 4
  add rax, [rsp + 40] ; 5

  ret 40

main:

  ; sum = add5(1, 2, 3, 4, 5);
  mov rax, 5
  push rax

  mov rax, 4
  push rax

  mov rax, 3
  push rax

  mov rax, 2
  push rax 

  mov rax, 1
  push rax

  call add5

  ; printf("The sum of those numbers is %d.\n", sum);
  mov rdi, resultFormat
  mov rsi, rax 
  mov rax, 0
  push r8 
  call printf 
  pop r8

  ; exit the program  
  mov rax, 0
  ret 

section .data 
  resultFormat db "The sum of those numbers is %d.", 0ah, 0dh, 0