#include "headers.h"


double **TestDet1 (int n, int c, int d) {
    double **a = CreateMatrix(n, n);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j && i != (n-1)) a[i][j] = c;
            else a[i][j] = d;
        }
    }
    return a;
}

double **TestInv1 (int n) {
    double **a = CreateMatrix(n, n);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i + j == n - 2) a[i][j] = -1;
            else if (i + j == n - 1) a[i][j] = 1;
            else a[i][j] = 0;
        }
    }
    return a;
}

double **TestHilbert (int n) {
    double **a = CreateMatrix(n, n);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            a[i][j] = 1.0 / (1 + i + j);
        }
    }
    return a;
}