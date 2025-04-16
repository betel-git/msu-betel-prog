#include "headers.h"

int main(void) {
    clock_t t1, t2;
    double seconds, eps = 1e-10;
    double **a;
    //double *b;
    double *x;
    double sum, err, res, temp;
    
    for (int k = 1; k < 10000; k = 2 * k) {

        x = (double *)malloc(k * sizeof(double));
        a = CreateMatrix(k , k + 1);
        RandomMatrix(a, k, k + 1, -1000, 1000);
        for (int i = 0; i < k; i++) {
            sum = 0;
            for (int j = 0; j < k; j++) {
                sum += a[i][j];
            }
            a[i][k] = sum;
        }

        if (k == 2) {
            printf("%le\n", a[0][0] + a[0][1]);
            printf("%le\n", a[1][0] + a[1][1]);
            PrintMatrix(a, k , k + 1);
        }
        t1 = clock();
        GaussianElimination(a, k, k + 1, eps);
        if (Rank(a, k, k, eps) != k) {
            return - 1;
        }
        Solver(a, x, k);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        fprintf(stdout, "\n");
        //fprintf(stdout, "Решение: \n");
        err = 0;
        res = 0;
        for (int i = 0; i < k; i++) {
            err += (x[i] - 1) * (x[i] - 1);
            temp = 0;
            for (int j = 0; j < k; j++) {
                temp += a[i][j] * x[j];
                //printf("a %d %d %le\n", i, j, a[i][j]);
            }
            //printf("%lg\n", temp - a[i][k]);
            res += (temp - a[i][k]) * (temp - a[i][k]);
        }
        
        printf("\nk = %d, time = %lf, err = %lg, res = %lg\n", k, seconds, sqrt(err), sqrt(res));
        FreeMatrix(a, k);
        free(x);
    }
    return 0;
}
 
