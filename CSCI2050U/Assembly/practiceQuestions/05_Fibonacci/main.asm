extern printf
extern scanf

global main 

section .data 
  nPrompt db "Enter an n value: ", 0
  nFormat db "%d", 0 ; "%lli", 0
  n dq 0
  resultFormat db "The %dth Fibonacci number is %d.", 0ah, 0dh, 0
  result dq 0

section .text

main:

  ; printf("Enter an n value: ");
  mov rdi, nPrompt
  mov rax, 0
  push r9
  call printf
  pop r9

  ; scanf("%d", &n);
  mov rdi, nFormat 
  mov rsi, n
  mov rax, 0
  push r9 
  call scanf 
  pop r9

  ; calculate the nth Fibonacci number

  ; calculate the nth Fibonacci number
  ; n                  - rdx
  ; count              - rsi
  ; previous Fibonacci - r11
  ; current Fibonacci  - r12
  mov rdx, [n]
  mov rsi, 1
  mov r11, 0
  mov r12, 1

  ; for (int i = 1; i <= n; i++) {
  ; while (i <= n) {

nextFibonacci:
  ; check the exit condition !(i < n)
  cmp rsi, rdx
  jge printResult

  ; calculate the next Fibonacci number (r11 + r12)
  mov r8, r12  ; old current Fibonacci (aka the new previous)
  add r12, r11 ; new current
  mov r11, r8  ; new previous

  ; i++
  inc rsi ; add rsi, 1

  ; goto nextFibonacci
  jmp nextFibonacci


printResult:
  mov [result], r12

  ; printf("The %dth Fibonacci number is %d.\n", n, result);
  mov rdi, resultFormat
  mov rsi, [n]
  mov rdx, [result]
  mov rax, 0
  push r9 
  call printf 
  pop r9

  ; exit the program
  ret 

