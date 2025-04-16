#include "headers.h"


// Функция для выделения памяти под матрицу
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


// Функция для освобождения памяти матрицы
double **FreeMatrix (double **a, int rows) {
    int i;
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        if (a[i] != NULL) free (a[i]);
    }
    free(a);
    return 0;
}


// Функция умножения матрицы на вектор
void Matrix_x_Vector (double** A, double* x, double* result, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        result[i] = 0.0;
        for (j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
}


// Функция вычисления нормы вектора (евклидова норма)
double VectorNorm (double* v, int n) {
    double norm = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        norm += v[i] * v[i];
    }
    return sqrt(norm);
}


// Функция для построения графика с помощью gnuplot
void Plot (const char* filename, int test) {
    FILE *script;
    if ((script = fopen("plot.gp", "w"))==NULL) {
        printf("plot.gp error\n");
        return;
    }
    fprintf(script, "set terminal pngcairo enhanced font 'Verdana,10'\n");
    fprintf(script, "set output 'data%d.png'\n", test);
    fprintf(script, "set title 'Сходимость метода'\n");
    fprintf(script, "set xlabel 'Итерация'\n");
    fprintf(script, "set ylabel 'Норма невязки'\n");
    //fprintf(script, "set logscale y\n");
    fprintf(script, "set grid\n");
    fprintf(script, "plot '%s' with lines title 'Норма невязки'\n", filename);
    //fprintf(script, "replot\n");
    fprintf(script, "exit\n");
    fclose(script);
    if (system("gnuplot plot.gp") != 0) {
        printf("Ошибка выполнения gnuplot\n");
    }
    remove("plot.gp");
}


// Метод простой итерации
int SimpleIteration (double** A, double* b, double* x, int n, double alpha, double eps, int max_iter, int test) {
    double* Ax = (double*)malloc(n * sizeof(double));
    double* r = (double*)malloc(n * sizeof(double));
    double* x_new = (double*)malloc(n * sizeof(double));
    
    int iter = 0, i;
    double norm_r;
    FILE *data;
    char filename[20];
    sprintf(filename, "1data%d.txt", test);
    
    if ((data = fopen(filename, "w"))==NULL) {
        printf("1data.txt error\n");
        return -1;
    }
    
    while (iter < max_iter) {
        // вычисляем A*x^k
        Matrix_x_Vector(A, x, Ax, n);
        // вычисляем r^k = A*x^k - b
        for (i = 0; i < n; i++) {
            r[i] = Ax[i] - b[i];
        }
        // вычисляем норму невязки для критерия остановки
        norm_r = VectorNorm(r, n);
        fprintf(data, "%d %.15e\n", iter, norm_r);
        
        if (norm_r < eps) {
            break;
        }
        // вычисляем новое приближение x^{k+1} = x^k - alpha * r^k
        for (i = 0; i < n; i++) {
            x_new[i] = x[i] - alpha * r[i];
        }
        // обновляем x для следующей итерации
        for (i = 0; i < n; i++) {
            x[i] = x_new[i];
        }
        iter++;
    }
    
    free(Ax);
    free(r);
    free(x_new);
    fclose(data);
    //printf("Норма невязки: %le\n", norm_r);

    Plot(filename, test);
    remove(filename);
    return iter;
}


// Функция вычисления скалярного произведения
double ScalarProduct (double* a, double* b, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }
    return result;
}


// Метод скорейшего спуска
int SpeedestDescent (double** A, double* b, double* x, int n, double epsilon, int max_iter, int test) {
    double* r = (double*)malloc(n * sizeof(double));
    double* Ar = (double*)malloc(n * sizeof(double));
    double alpha;
    int iter = 0;
    double norm_r;
    FILE *data;
    char filename[20];
    sprintf(filename, "2data%d.txt", test);
    
    if ((data = fopen(filename, "w"))==NULL) {
        printf("2data.txt error\n");
        return -1;
    }
    
    // вычисляем начальную невязку r = Ax - b
    Matrix_x_Vector(A, x, r, n);
    for (int i = 0; i < n; i++) {
        r[i] -= b[i];
    }
    
    while (iter < max_iter) {
        // Вычисляем Ar
        Matrix_x_Vector(A, r, Ar, n);
        alpha = ScalarProduct(r, r, n) / ScalarProduct(r, Ar, n);
        // обновляем решение x = x - alpha*r
        for (int i = 0; i < n; i++) {
            x[i] -= alpha * r[i];
        }
        // обновляем невязку r = Ax - b
        Matrix_x_Vector(A, x, r, n);
        for (int i = 0; i < n; i++) {
            r[i] -= b[i];
        }
        norm_r = sqrt(ScalarProduct(r, r, n));
        fprintf(data, "%d %.15e\n", iter, norm_r);
        if (norm_r < epsilon) {
            break;
        }
        iter++;
    }
    free(r);
    free(Ar);
    fclose(data);
    Plot(filename, test * 10);
    remove(filename);
    return iter;
}


// Метод Гаусса-Зейделя
int GaussSeidel (double** A, double* b, double* x, int n, double epsilon, int max_iter, int test) {
    double* x_new = (double*)malloc(n * sizeof(double)); // Новое приближение
    int iter, i, j;
    double diff_norm, sum;
    FILE *data;
    char filename[20];
    sprintf(filename, "3data%d.txt", test);
    
    if ((data = fopen(filename, "w"))==NULL) {
        printf("3data.txt error\n");
        return -1;
    }
    
    for (iter = 0; iter < max_iter; iter++) {
        for (i = 0; i < n; i++) {
            x_new[i] = x[i];
        }
        // обновляем каждую компоненту решения
        for (i = 0; i < n; i++) {
            sum = 0.0;
            // суммируем уже обновленные компоненты (j < i)
            for (j = 0; j < i; j++) {
                sum += A[i][j] * x_new[j];
            }
            // суммируем еще не обновленные компоненты (j > i)
            for (j = i + 1; j < n; j++) {
                sum += A[i][j] * x[j];
            }
            // вычисляем новое значение x[i]
            x_new[i] = (b[i] - sum) / A[i][i];
        }
        // вычисляем норму разницы между итерациями
        diff_norm = 0.0;
        for (i = 0; i < n; i++) {
            diff_norm += (x_new[i] - x[i]) * (x_new[i] - x[i]);
        }
        diff_norm = sqrt(diff_norm);

        for (i = 0; i < n; i++) {
            x[i] = x_new[i];
        }

        fprintf(data, "%d %.15e\n", iter, diff_norm);
        if (diff_norm < epsilon) {
            break;
        }
    }
    free(x_new);
    fclose(data);
    Plot(filename, test * 100);
    remove(filename);
    return iter;
}