#include "headers.h"

int main(void) {
    clock_t t1, t2;
    double seconds, eps = 1e-10;
    double **a;
    double res;
    
    for (int k = 1; k < 1000; k++) {
        a = CreateMatrix(k , k);
        RandomMatrix(a, k, k, -1000, 1000);
        if (k == 2) PrintMatrix(a, k , k);
        t1 = clock();
        res = Determinant(a, k, k, eps);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        printf("k = %d, time = %lf sec, det = %lg\n", k, seconds, res);
    }
    return 0;
}
