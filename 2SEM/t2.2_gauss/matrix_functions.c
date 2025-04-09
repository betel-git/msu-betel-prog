#include "headers.h"

// процедура освобождения памяти матрицы
double **FreeMatrix (double **a, int rows) {
    int i;
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        if (a[i] != NULL) free (a[i]);
    }
    free(a);
    return 0;
}

// процедура выделения памяти для матрицы и её создания
double **CreateMatrix (int rows, int cols) {
    int i, j;
    double **a;
    a = (double **)malloc(rows * sizeof(double *));
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        a[i] = (double *)malloc(cols * sizeof(double));
        if (a[i] == NULL) {
            FreeMatrix(a, i);
            return NULL;
        }
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            a[i][j] = 0;
        }
    }
    return a;
}

// процедура для выравнивания слолбцов при выводе матриц
int MaxNumberLength(double **a, int rows, int cols) {
    int max_len = 0, current_len, i, j;
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            current_len = snprintf(NULL, 0, "%le", a[i][j]);
            if (current_len > max_len) {
                max_len = current_len;
            }
        }
    }
    return max_len;
}

// процедура печати матрицы
void PrintMatrix(double **a, int rows, int cols) {
    int i, j, num_width = MaxNumberLength(a, rows, cols) + 1;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(stdout, "%*le", num_width, a[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

// процедура печати матрицы (для СЛУ)
void PrintMatrix2(double **a, int rows, int cols) {
    int i, j, num_width = MaxNumberLength(a, rows, cols) + 1;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols - 1; j++) {
            fprintf(stdout, "%*le", num_width, a[i][j]);
        }
        fprintf(stdout, " | %*le", num_width, a[i][j]);
        fprintf(stdout, "\n");
    }
}

// процедура умножения двух матриц
double **MatrixMultiplication (double **a, double **b, int m1, int n1, int m2, int n2) {
    int i, j, l;
    double **res;
    if (n1 != m2) return NULL;
    res = CreateMatrix(m1, n2);
    if (res == NULL) return NULL;
    for (i = 0; i < m1; i++) {
        for (j = 0; j < n2; j++) {
            res[i][j] = 0;
            for (l = 0; l < n1; l++) {
                res[i][j] += a[i][l] * b[l][j];
            }
        }
    }
    return res;
}
