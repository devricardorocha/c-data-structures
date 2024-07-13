#include <stdbool.h>
#include <stdio.h>

#define MAX 100000000

bool printFibonacci(int oldVal, int curVal) {

    if (curVal <= MAX) {
        printf("%i ", oldVal);
        printFibonacci(curVal, oldVal + curVal);
    }

    return false;
}

int main() {
    printFibonacci(1,1);
    return 0;
}