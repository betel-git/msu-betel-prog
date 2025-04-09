#include "headers.h"


void TestRank (FILE *in, double eps, int *err) {
    double **a;
    int i, j, rows, cols;
    double mult = 1;
    *err = *err + 0; // временная заглушка
    fprintf(stdout, "ТЕСТ НА РАНГ МАТРИЦЫ\n\n");

    fscanf(in, "%d %d", &rows, &cols);

    a = CreateMatrix(rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(in, "%lg", &a[i][j]);
        }
    }
    fprintf(stdout, "Исходная матрица:\n");
    PrintMatrix(a, rows, cols);
    fprintf(stdout, "\n");
    fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
    ConstMultiplication(a, rows, cols, mult); // умножение на константу
    GaussianElimination(a, rows, cols, eps);
    fprintf(stdout, "Матрица ступенчатого вида:\n");
    PrintMatrix(a, rows, cols);
    fprintf(stdout, "\n");
    fprintf(stdout, "Ранг матрицы: %d\n", Rank(a, rows, cols, eps));
    //FreeMatrix(a, rows);
    fprintf(stdout, "----------------\n\n");
    fclose(in);
}


void TestDet (FILE *in, double eps, int *err) {
    double **a;
    int i, j, rows, cols;
    double mult = 1;
    *err = *err + 0; // временная заглушка
    fprintf(stdout, "ТЕСТ НА ОПРЕДЕЛИТЕЛЬ МАТРИЦЫ\n\n");


    fscanf(in, "%d %d", &rows, &cols);

    a = CreateMatrix(rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(in, "%lg", &a[i][j]);
        }
    }

    fprintf(stdout, "Исходная матрица:\n");
    PrintMatrix(a, rows, cols);
    fprintf(stdout, "\n");
    fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
    ConstMultiplication(a, rows, cols, mult); // умножение на константу
    fprintf(stdout, "Определитель матрицы: %lg\n\n", Determinant(a, rows, cols, eps));
    fprintf(stdout, "Матрица ступенчатого вида:\n");
    PrintMatrix(a, rows, cols);
    fprintf(stdout, "----------------\n\n");
    FreeMatrix(a, rows);
    fclose(in);
}


void TestSolver (FILE *in, double eps, int *err) {
    double **a;
    int i, j, rows, cols;
    //double mult = 1;
    double *x;
    fprintf(stdout, "ТЕСТ НА РЕШЕНИЕ СЛУ\n\n");

    fscanf(in, "%d %d", &rows, &cols);
    if (rows != cols) {
        fclose(in);
        *err = -3;
        return;
    }

    a = CreateMatrix(rows, cols + 1);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols + 1; j++) {
            fscanf(in, "%lg", &a[i][j]);
        }
    }
    x = (double *)malloc(rows * sizeof(double));
    if (x == NULL) {
        fclose(in), FreeMatrix(a, rows);
        *err = -1;
        return;
    }


    fprintf(stdout, "Исходная матрица:\n");
    PrintMatrix2(a, rows, cols + 1);
    fprintf(stdout, "\n");
    //fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
    //ConstMultiplication(a, rows, cols, mult); // умножение на константу
    GaussianElimination(a, rows, cols + 1, eps);
    fprintf(stdout, "Матрица ступенчатого вида:\n");
    PrintMatrix2(a, rows, cols + 1);
    if (Rank(a, rows, cols, eps) != rows) {
        *err = -2;
        return;
    }
    Solver(a, x, cols);
    fprintf(stdout, "\n");
    fprintf(stdout, "Решение: \n");
    for (i = 0; i < rows; i++) {
        fprintf(stdout, "%lf ", x[i]);
    }
    fprintf(stdout, "\n");
    fprintf(stdout, "----------------\n\n");
    FreeMatrix(a, rows);
    free(x);
    fclose(in);
}


void TestInverse (FILE *in, double eps, int *err) {
    double **a, **b;
    int i, j, rows, cols;
    //double mult = 1;
    fprintf(stdout, "ТЕСТ НА НАХОЖДЕНИЕ ОБРАТНОЙ МАТРИЦЫ\n\n");

    fscanf(in, "%d %d", &rows, &cols);
    if (rows != cols) {
        fclose(in);
        *err = -3;
        return;
    }

    a = CreateMatrix(rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fscanf(in, "%lg", &a[i][j]);
        }
    }

    fprintf(stdout, "Исходная матрица:\n");
    PrintMatrix(a, rows, cols);
    fprintf(stdout, "\n");
    //fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
    //ConstMultiplication(a, rows, cols, mult); // умножение на константу
    b = GaussianPlusInverse(a, rows, cols, eps);
    fprintf(stdout, "Обратная матрица:\n");
    PrintMatrix(b, rows, cols);
    if (Rank(a, rows, cols, eps) != rows) {
        *err = -2;
        return;
    }
    fprintf(stdout, "\n");
    FreeMatrix(a, rows);
    FreeMatrix(b, rows);
    fclose(in);
}


int main(void) {
    int err = 0;
    double eps = 1e-17;
    FILE *out, *in, *in2, *in3, *in4;

    if ((in = fopen("input_mxn.txt", "r"))==NULL) {
        printf("input_mxn.txt error\n");
        return -1;
    }

    if ((in2 = fopen("input_nxn.txt", "r"))==NULL) {
        printf("input_nxn.txt error\n");
        fclose(in);
        return -1;
    }

    if ((in3 = fopen("input_sys.txt", "r"))==NULL) {
        printf("input_sys.txt error\n");
        fclose(in), fclose(in2);
        return -1;
    }

    if ((in4 = fopen("input_inv.txt", "r"))==NULL) {
        printf("input_inv.txt error\n");
        fclose(in), fclose(in2), fclose(in3);
        return -1;
    }

    //freopen("output.txt", "w", stdout); // закомментируйте эту строку, если нужен вывод в консоль
    if ((out = freopen("output.txt", "w", stdout))==NULL) {
        printf("output.txt error\n");
        fclose(in), fclose(in2), fclose(in3), fclose(in4);
        return -1;
    }

    TestRank(in, eps, &err);
    TestDet(in2, eps, &err);
    TestSolver(in3, eps, &err);
    TestInverse(in4, eps, &err);
    
    fclose(out);
    return 0;
}