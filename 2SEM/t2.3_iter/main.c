#include "headers.h"


double **Test1 (int n) {
    double **a = CreateMatrix(n, n);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) a[i][j] = n;
            else if (j == i + 1 || i == j + 1) a[i][j] = -1;
            else a[i][j] = 0;
        }
    }
    return a;
}


int main(void) {
    int n, i, j, iterations, test = 1;
    double alpha, eps, norm_r;
    int max_iter;
    double **A;
    double *x, *x1, *x2, *b, *Ax;
    FILE *in;

    freopen("output.txt", "w", stdout); // закомментируйте эту строку, если нужен вывод в консоль

    if ((in = fopen("input.txt", "r"))==NULL) {
        printf("input.txt error\n");
        return -1;
    }

    while (!feof(in)) {
        fscanf(in, "%d", &n);
        
        // выделяем память под матрицу и векторы b и x0
        A = CreateMatrix(n, n);
        b = (double*)malloc(n * sizeof(double));
        x = (double*)malloc(n * sizeof(double));
        x1 = (double*)malloc(n * sizeof(double));
        x2 = (double*)malloc(n * sizeof(double));
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                fscanf(in, "%lf", &A[i][j]);
            }
        }
        
        for (i = 0; i < n; i++) {
            fscanf(in, "%lf", &b[i]);
        }
        
        for (i = 0; i < n; i++) {
            fscanf(in, "%lf", &x[i]);
            x1[i] = x[i];
            x2[i] = x[i];
        }
        
        fscanf(in, "%lf", &alpha);
        fscanf(in, "%lf", &eps);
        fscanf(in, "%d", &max_iter);

        iterations = SimpleIteration(A, b, x, n, alpha, eps, max_iter, test);
        
        printf("INPUT TEST %d (простые итерации):\n", test);
        printf("Количество итераций: %d\n", iterations);
        iterations = 0;
        printf("Решение x:\n");
        for (i = 0; i < n; i++) {
            printf("x[%d] = %.10f\n", i, x[i]);
        }
        
        // проверка невязки
        Ax = (double*)malloc(n * sizeof(double));
        Matrix_x_Vector(A, x, Ax, n);
        norm_r = 0.0;
        for (i = 0; i < n; i++) {
            norm_r += (Ax[i] - b[i]) * (Ax[i] - b[i]);
        }
        norm_r = sqrt(norm_r);
        printf("Точность: %le\n\n", norm_r);
        free(Ax);


        iterations = SpeedestDescent(A, b, x1, n, eps, max_iter, test);

        printf("INPUT TEST %d (скорейший спуск):\n", test);
        printf("Количество итераций: %d\n", iterations);
        iterations = 0;
        printf("Решение x:\n");
        for (i = 0; i < n; i++) {
            printf("x[%d] = %.10f\n", i, x1[i]);
        }
        
        // проверка невязки
        Ax = (double*)malloc(n * sizeof(double));
        Matrix_x_Vector(A, x1, Ax, n);
        norm_r = 0.0;
        for (i = 0; i < n; i++) {
            norm_r += (Ax[i] - b[i]) * (Ax[i] - b[i]);
        }
        norm_r = sqrt(norm_r);
        printf("Точность: %le\n\n", norm_r);


        iterations = GaussSeidel(A, b, x2, n, eps, max_iter, test);

        printf("INPUT TEST %d (Гаусс-Зейдель):\n", test);
        printf("Количество итераций: %d\n", iterations);
        iterations = 0;
        printf("Решение x:\n");
        for (i = 0; i < n; i++) {
            printf("x[%d] = %.10f\n", i, x2[i]);
        }
        
        // проверка невязки
        Ax = (double*)malloc(n * sizeof(double));
        Matrix_x_Vector(A, x2, Ax, n);
        norm_r = 0.0;
        for (i = 0; i < n; i++) {
            norm_r += (Ax[i] - b[i]) * (Ax[i] - b[i]);
        }
        norm_r = sqrt(norm_r);
        printf("Точность: %le\n\n", norm_r);
        
        FreeMatrix(A, n);
        free(b);
        free(x);
        free(x1);
        free(x2);
        free(Ax);
        test++;
        printf("-------------\n");
    }
    fclose(in);



    printf("OTHER TEST:\n");
    n = 18;
    A = Test1(n);
    b = (double*)malloc(n * sizeof(double));
    x = (double*)malloc(n * sizeof(double));
    x1 = (double*)malloc(n * sizeof(double));
    x2 = (double*)malloc(n * sizeof(double));
    for (i = 0; i < n; i++) b[i] = n - i - 1;
    for (i = 0; i < n; i++) {
    x[i] = 0;
    x1[i] = 0;
    x2[i] = 0; 
    }
    alpha = 0.1;
    eps = 1e-15;
    max_iter = 5000;

    iterations = SimpleIteration(A, b, x, n, alpha, eps, max_iter, test);
        
    printf("Количество итераций: %d\n", iterations);
    iterations = 0;
    printf("Решение x:\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] = %.10f\n", i, x[i]);
    }
    
    // проверка невязки
    Ax = (double*)malloc(n * sizeof(double));
    Matrix_x_Vector(A, x, Ax, n);
    norm_r = 0.0;
    for (i = 0; i < n; i++) {
        norm_r += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    }
    norm_r = sqrt(norm_r);
    printf("Точность: %le\n\n", norm_r);


    iterations = SpeedestDescent(A, b, x1, n, eps, max_iter, test);
        
    printf("Количество итераций: %d\n", iterations);
    iterations = 0;
    printf("Решение x:\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] = %.10f\n", i, x1[i]);
    }
    
    // проверка невязки
    Ax = (double*)malloc(n * sizeof(double));
    Matrix_x_Vector(A, x1, Ax, n);
    norm_r = 0.0;
    for (i = 0; i < n; i++) {
        norm_r += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    }
    norm_r = sqrt(norm_r);
    printf("Точность: %le\n\n", norm_r);



    iterations = GaussSeidel(A, b, x2, n, eps, max_iter, test);
        
    printf("Количество итераций: %d\n", iterations);
    iterations = 0;
    printf("Решение x:\n");
    for (i = 0; i < n; i++) {
        printf("x[%d] = %.10f\n", i, x2[i]);
    }
    
    // проверка невязки
    Ax = (double*)malloc(n * sizeof(double));
    Matrix_x_Vector(A, x2, Ax, n);
    norm_r = 0.0;
    for (i = 0; i < n; i++) {
        norm_r += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    }
    norm_r = sqrt(norm_r);
    printf("Точность: %le\n\n", norm_r);
    
    FreeMatrix(A, n);
    free(b);
    free(x);
    free(x1);
    free(x2);
    free(Ax);

    return 0;
}