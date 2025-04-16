#include "headers.h"


void TestRank (FILE *in, double eps, int *err) {
    double **a;
    int i, j, rows, cols;
    //double mult = 1;
    *err = *err + 0; // временная заглушка
    fprintf(stdout, "ТЕСТ НА РАНГ МАТРИЦЫ\n\n");

    while (!feof(in)) {
        fscanf(in, "%d %d", &rows, &cols);

        a = CreateMatrix(rows, cols);
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                fscanf(in, "%lg", &a[i][j]);
            }
        }
        fprintf(stdout, "Исходная матрица:\n");
        //fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
        //ConstMultiplication(a, rows, cols, mult); // умножение на константу
        PrintMatrix(a, rows, cols);
        fprintf(stdout, "\n");
        GaussianElimination(a, rows, cols, eps);
        fprintf(stdout, "Матрица ступенчатого вида:\n");
        PrintMatrix(a, rows, cols);
        fprintf(stdout, "Ранг матрицы: %d\n\n", Rank(a, rows, cols, eps));
        FreeMatrix(a, rows);
        fprintf(stdout, "----------------\n\n");
    }
    fclose(in);
}


void TestDet (FILE *in, double eps, int *err) {
    double **a;
    int i, j, rows, cols;
    //double mult = 1;
    *err = *err + 0; // временная заглушка
    fprintf(stdout, "ТЕСТ НА ОПРЕДЕЛИТЕЛЬ МАТРИЦЫ\n\n");

    while (!feof(in)) {
        fscanf(in, "%d %d", &rows, &cols);

        a = CreateMatrix(rows, cols);
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                fscanf(in, "%lg", &a[i][j]);
            }
        }

        fprintf(stdout, "Исходная матрица:\n");
        //fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
        //ConstMultiplication(a, rows, cols, mult); // умножение на константу
        PrintMatrix(a, rows, cols);
        fprintf(stdout, "\n");
        fprintf(stdout, "Определитель матрицы: %lg\n\n", Determinant(a, rows, cols, eps));
        fprintf(stdout, "Матрица ступенчатого вида:\n");
        PrintMatrix(a, rows, cols);
        FreeMatrix(a, rows);
        fprintf(stdout, "----------------\n\n");
    }

    fclose(in);
}


void TestSolver (FILE *in, double eps, int *err) {
    double **a;
    int i, j, rows, cols;
    //double mult = 1;
    double *x;
    fprintf(stdout, "ТЕСТ НА РЕШЕНИЕ СЛУ\n\n");

    while (!feof(in)) {
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
        //fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
        //ConstMultiplication(a, rows, cols, mult); // умножение на константу
        PrintMatrix2(a, rows, cols + 1);
        fprintf(stdout, "\n");
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
        FreeMatrix(a, rows);
        free(x);
        fprintf(stdout, "\n");
        fprintf(stdout, "----------------\n\n");
    }
    fclose(in);
}


void TestInverse (FILE *in, double eps, int *err) {
    double **a, **b;
    int i, j, rows, cols;
    //double mult = 1;
    fprintf(stdout, "ТЕСТ НА НАХОЖДЕНИЕ ОБРАТНОЙ МАТРИЦЫ\n\n");

    while(!feof(in)) {
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
        //fprintf(stdout, "Элементы матрицы умножаются на %lg\n\n", mult = 1);
        //ConstMultiplication(a, rows, cols, mult); // умножение на константу
        PrintMatrix(a, rows, cols);
        fprintf(stdout, "\n");
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
    }
    fclose(in);
}


int main(void) {
    int err = 0;
    double eps = 1e-15;
    FILE *in, *in2, *in3, *in4;
    int c, d, n;
    double **a, **b;

    if ((in = fopen("input_rk.txt", "r"))==NULL) {
        printf("input_rk.txt error\n");
        return -1;
    }

    if ((in2 = fopen("input_det.txt", "r"))==NULL) {
        printf("input_det.txt error\n");
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

    freopen("output.txt", "w", stdout); // закомментируйте эту строку, если нужен вывод в консоль

    TestRank(in, eps, &err);
    fprintf(stdout, "-------------------------------------------------\n");
    TestDet(in2, eps, &err);
    fprintf(stdout, "-------------------------------------------------\n");
    TestSolver(in3, eps, &err);
    fprintf(stdout, "-------------------------------------------------\n");
    TestInverse(in4, eps, &err);
    fprintf(stdout, "-------------------------------------------------\n");

    fprintf(stdout, "ПРОЧИЕ ТЕСТЫ\n");
    fprintf(stdout, "ТЕСТ 1\n");
    c = 3, d = 2, n = 5;
    a = TestDet1(n, c, d);
    PrintMatrix(a, n, n);
    fprintf(stdout, "det = %le, true det (== d(c - d)^{n - 1}) = %le", Determinant(a, n, n, eps), d * pow(c - d, n - 1)); // == d(c - d)^{n - 1}
    FreeMatrix(a, n);

    fprintf(stdout, "\n\nТЕСТ 2\n");
    fprintf(stdout, "Изначальная матрица: \n");
    a = TestInv1(n);
    PrintMatrix(a, n, n);
    fprintf(stdout, "Обратная матрица: \n");
    b = GaussianPlusInverse(a, n, n, eps);
    PrintMatrix(b, n, n);
    fprintf(stdout, "Правильно: a_{ij}^-1 = 1 if i + j geq n - 1; else 0\n");
    FreeMatrix(a, n);
    FreeMatrix(b, n);

    n = 5;
    fprintf(stdout, "\n\nТЕСТ 3\n");
    fprintf(stdout, "Изначальная матрица Гильберта: \n");
    a = TestHilbert(n);
    PrintMatrix(a, n, n);
    b = GaussianPlusInverse(a, n, n, eps);
    fprintf(stdout, "Ступенчатый вид матрицы: \n");
    PrintMatrix(a, n, n);
    fprintf(stdout, "Обратная матрица: \n");
    PrintMatrix(b, n, n);
    FreeMatrix(b, n);

    FreeMatrix(a, n);
    a = TestHilbert(n);
    fprintf(stdout, "det = %le, rk = %d\n", Determinant(a, n, n, eps), Rank(a, n, n, eps));
    FreeMatrix(a, n);

    return 0;
}