#include "headers.h"

int main(void) {
    double **a, **b;
    int i, j, rows, cols;
    double eps = 1e-15;
    double *x;

    printf("rows cols: ");
    scanf("%d %d", &rows, &cols);

    a = CreateMatrix(rows, cols);
    printf("matrix: \n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%lg", &a[i][j]);
        }
    }

    printf("rk = 1, det = 2, sle = 3, inv = 4: ");
    scanf("%d", &i);
    switch (i)
    {
    case 1:
        printf("rk = %d\n", Rank(a, rows, cols, eps));
        break;
    case 2:
        printf("det = %lg\n", Determinant(a, rows, cols, eps));
        break;
    case 3:
        x = (double *)malloc(rows * sizeof(double));
        Solver(a, x, rows);
        for (i = 0; i < rows; i++) {
            printf("%le ", x[i]);
        }
        printf("\n");
        break;
    case 4:
        b = GaussianPlusInverse(a, rows, cols, eps);
        PrintMatrix(b, rows, cols);
        break;
    default:
        printf("error\n");
        break;
    }
    FreeMatrix(a, rows);
    return 0;
}