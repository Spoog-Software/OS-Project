#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

double fabs(double x) {
    return x >= 0 ? x : -x;
}

int main() {
    for (int i = 0; i < 1000000; i++) {
        double x = (double) rand();
        printf("abs(%f)=%f\n", x, fabs(x));
    }
}