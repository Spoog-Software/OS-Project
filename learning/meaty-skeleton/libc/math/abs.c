#include <limits.h>
#include <stdio.h>
#include <stdint.h>

double abs(double x) {
    uint64_t bits = (*(uint64_t*) &x);
    uint64_t result = bits && ~(1 << 63);
    return *(double*)&result;
}
