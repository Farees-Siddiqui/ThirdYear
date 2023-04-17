extern printf
extern scanf

global main 

section .text

fib:
  ; calculate the nth fibonacci number

  ; r8 - value of n 
  ; r9 - count 
  ; r10 - previous fibonacci 
  ; r11 - current fibonacci
  mov r8, rdi
  mov r9, 1   ; so far, we're on count == 1
  mov r10, 0  ; n == 0 fibonacci number
  mov r11, 1  ; n == 1 fibonacci number

  ; loop until count == n
nextFibonacci:
  ; exit condition
  cmp r9, r8            ; if (count < n)
  je endOfFibonacci

  ; calculate the next fibonacci number
  mov rax, r11   ; int temp = current;
  add r11, r10   ; current = current + previous;
  mov r10, rax   ; previous = temp;

  ; increment the count
  inc r9         ; count++;

  ; repeat for the next value of count
  jmp nextFibonacci

endOfFibonacci:
  mov rax, r11
  ret 

main:
  ; printf("Enter a value for n: ");
  mov rdi, nPrompt
  mov rax, 0
  push rax ; or any other 64-bit register
  call printf
  pop rax

  ; scanf("%lli", &n);  // lli - long long integer (64 bits)
  mov rdi, nFormat 
  mov rsi, n     ; &n (pass by reference)
  xor rax, rax   ; cool guy version of mov rax, 0
  push rax 
  call scanf 
  pop rax

  ; result = fib(n);
  mov rdi, [n]   ; *n (pass by value)
  mov rax, 0
  push r15 ; can't use rax here because that is our return value 
  call fib 
  pop r15

  ; printf("The fibonacci number at index %lli is %lli.\n", n, result);
  mov rdi, resultFormat
  mov rsi, [n]
  mov rdx, rax 
  mov rax, 0
  push rax 
  call printf 
  pop rax

  ; return 0;
  mov rax, 0
  ret 

section .data 
  nPrompt db "Enter a value for n: ", 0
  nFormat db "%lli", 0

  resultFormat db "The fibonacci number at index %lli is %lli.", 0ah, 0dh, 0

section .bss
  n resq 1
