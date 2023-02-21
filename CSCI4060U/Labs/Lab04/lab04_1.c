#include <stdio.h>
#include <math.h>

int fib(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fib(n-1) + fib(n-2);
    }
}

int main() {
    printf("%d ", fib(30));

    return 0;
}
