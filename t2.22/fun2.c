#include "greatestsequence.h"
#include <limits.h>
#include <stdio.h>

int GreatestSequence (int *x, size_t size) {
    size_t i;
    int last = INT_MIN, boolean = 0, count = 0, res = 0, current = 0;
    for (i = 1; i < size; i++) {
        if (x[i] >= x[i - 1]) {
            count += 1;
            if (boolean) {
                count += 1;
                boolean = 0;
            }
        }
        else {
            if (count > res) {
                res = count;
                count = 0;
            }
            boolean = 1;
        }
        current = x[i];
        fprintf(stdout, "current %i\n", current);
        fprintf(stdout, "count %i\n", count);
    }
    if (count > res) {
        res = count;
    }
    return res;
}