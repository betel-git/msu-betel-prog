#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void PrintMatrix (long long int **a, int rows, int cols, FILE *out);
long long int **FreeMatrix (long long int **a, int rows);
long long int **CreateMatrix (int rows, int cols);

// автотест не проверяет программу на утечки памяти, но всё же надёжнее будет закрывать все файлы
// и освобождать всю память — вопрос в 10 строках во FreeMatrix и ещё в каком-то количестве
// во всех проверках, но зато на этой стороне точно не будет проблем

void PrintMatrix (long long int **a, int rows, int cols, FILE *out) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(out, "%lld ", a[i][j]);
        }
        fprintf(out, "\n");
    }
}


long long int **FreeMatrix (long long int **a, int rows) {
    int i;
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        if (a[i] != NULL) free (a[i]);
    }
    free(a);
    return NULL;
}


long long int **CreateMatrix (int rows, int cols) {
    int i, j;
    long long int **a;
    a = (long long int **)malloc(rows * sizeof(long long int *));
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        a[i] = (long long int *)malloc(cols * sizeof(long long int));
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


int main(void) {
    // буквы L и K не информативны, поэтому я планирую сразу их переобозначить
    // L = rows, K = cols
    int M, N, rows, cols;
    int i, j, k, l;
    long long int **a, **c;
    FILE *in, *out;
    int *cls, *rws;
    int check = 0;
    //int newrw = 0, newcl = 0;
    //double EPS = 1e-15;

    // прочитать входной файл
    in = fopen("data.txt", "r");
    if(!in) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    // прочитать выходной файл
    out = fopen("res.txt", "w");
    if(!out) {
        perror("Ошибка открытия выходного файла");
        fclose(out);
        return -1;
    }

    // прочитать M N L(rows) K(cols) 
    if (fscanf(in, "%d", &M) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано M\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    if (fscanf(in, "%d", &N) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано N\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    if (fscanf(in, "%d", &rows) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано L\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    if (fscanf(in, "%d", &cols) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано K\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    // проверить, что количество строк и столбцов неотрицательно
    if (rows < 0 || cols < 0) {
        fclose(in);
        fclose(out);
        printf("Отрицательные значения количества строк или столбцов\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    // создать массивы, в которые в будущем будем записывать на i позицию 1, если i строка (столбец) входят в подмножество
    // 0 — иначе
    rws = (int *)malloc(rows * sizeof(int));
    if (rws == NULL) {
        fclose(in);
        fclose(out);
        printf("Ошибка создания массива rws\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    cls = (int *)malloc(cols * sizeof(int));
    if (cls == NULL) {
        fclose(in);
        fclose(out);
        free(rws);
        printf("Ошибка создания массива cls\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    // создать основную матрицу
    a = CreateMatrix(rows, cols);
    if (a == NULL) {
        fclose(in);
        fclose(out);
        free(rws);
        free(cls);
        printf("Ошибка при создании матрицы A\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    // условие «элементы, не принадлежащие множеству X, не должны измениться»
    // наводит на мысль, что можно тупо
    // создать вторую матрицу, которая будет копией первой и будет всё время неизменной
    c = CreateMatrix(rows, cols);
    if (c == NULL) {
        fclose(in);
        fclose(out);
        free(rws);
        free(cls);
        FreeMatrix(a, rows);
        printf("Ошибка при создании матрицы C\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    // прочитать элементы матрицы и записать их в a и c
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (fscanf(in, "%lld", &a[i][j]) != 1) {
                FreeMatrix(a, rows);
                fclose(in);
                fclose(out);
                free(rws);
                free(cls);
                printf("Ошибка чтения значения элемента матрицы\n");
                fprintf(out, "ERROR\n");
                return -1;
            }
            c[i][j] = a[i][j];
        }
    }
    fclose(in);
    
    // определить какие строки входят в подмножество (условие проверки меняется от задачи)
    for (i = 0; i < rows; i++) {
        rws[i] = 0;
        for (j = 0; j < cols; j++) {
            if ((a[i][j] >= M) && (a[i][j] <= N)) {
                rws[i] = 1;
                break;
            }
        }
    }
    
    // определить какие столбцы входят в подмножество (условие проверки меняется от задачи)
    for (j = 0; j < cols; j++) {
        cls[j] = 0;
        for (i = 0; i < rows; i++) {
            if ((a[i][j] >= M) && (a[i][j] <= N)) {
                cls[j] = 1;
                break;
            }
        }
    }
    
    // почти всегда будет 4 вложенных цикла - в первых двух пробегаем все элементы матрицы
    // в последних двух с какими-то условиями ищем нужный элемент в ИСХОДНОЙ матрице c
    for (i = 0; i < rows; i++) {
        if (rws[i] == 0) continue; // если строка не лежит в подмножестве, то переходим на следующую итерацию
        for (j = 0; j < cols; j++) {
            check = 0;
            if (cls[j] == 0) continue; // если столбец не лежит в подмножестве, то переходим на следующую итерацию
            for (k = 0; k < rows; k++) {
                //if (rws[k] == 0) continue;
                for (l = 0; l < j; l++) {
                    if (cls[l] == 0) continue;
                    if (a[i][j] == c[k][l]) {
                        a[i][j] = 1;
                        check = 1;
                        break;
                    }
                }
                if (check == 1) break;
            }
            if (check == 0) a[i][j] = 0;
        }
    }
    
    // вывести M N K L и распечатать матрицу
    fprintf(out, "%d %d %d %d\n", M, N, rows, cols);
    PrintMatrix(a, rows, cols, out);

    // закрыть всё, освободить всю память
    fclose(out);
    FreeMatrix(a, rows);
    FreeMatrix(c, rows);
    free(cls);
    free(rws);
    return 0;
} 


/* #include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **FreeMatrix (double **a, int rows);
double **CreateMatrix (int rows, int cols);
void PrintMatrix(double **a, int rows, int cols, FILE *out);


void PrintMatrix (double **a, int rows, int cols, FILE *out) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(out, "%lg ", a[i][j]);
        }
        fprintf(out, "\n");
    }
}


double **FreeMatrix (double **a, int rows) {
    int i;
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        if (a[i] != NULL) free (a[i]);
    }
    free(a);
    return NULL;
}


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


int main(void) {
    // L = rows, K = cols
    int M, N, L, K;
    int i, j, k, l;
    double **a, **c;
    FILE *in, *out;
    int *cls, *rws;
    int check = 0;
    //int newrw = 0, newcl = 0;
    double EPS = 1e-15;

    in = fopen("data.txt", "r");
    if(!in) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    out = fopen("res.txt", "w");
    if(!out) {
        perror("Ошибка открытия выходного файла");
        fclose(out);
        return -1;
    }

    if (fscanf(in, "%d", &M) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано M\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    if (fscanf(in, "%d", &N) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано N\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    if (fscanf(in, "%d", &L) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано L\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    if (fscanf(in, "%d", &K) != 1) {
        fclose(in);
        fclose(out);
        printf("Не прочитано K\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    if (L < 0 || K < 0) {
        fclose(in);
        fclose(out);
        printf("Отрицательные значения количества строк или столбцов\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    rws = (int *)malloc(L * sizeof(int));
    if (rws == NULL) {
        fclose(in);
        fclose(out);
        printf("Ошибка создания массива rws\n");
        fprintf(out, "ERROR\n");
        return -1;
    }
    
    cls = (int *)malloc(K * sizeof(int));
    if (cls == NULL) {
        fclose(in);
        fclose(out);
        free(rws);
        printf("Ошибка создания массива cls\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    a = CreateMatrix(L, K);
    if (a == NULL) {
        fclose(in);
        fclose(out);
        free(rws);
        free(cls);
        printf("Ошибка при создании матрицы A\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    c = CreateMatrix(L, K);
    if (c == NULL) {
        fclose(in);
        fclose(out);
        free(rws);
        free(cls);
        FreeMatrix(a, L);
        printf("Ошибка при создании матрицы C\n");
        fprintf(out, "ERROR\n");
        return -1;
    }

    for (i = 0; i < L; i++) {
        for (j = 0; j < K; j++) {
            if (fscanf(in, "%lf", &a[i][j]) != 1) {
                FreeMatrix(a, L);
                fclose(in);
                fclose(out);
                free(rws);
                free(cls);
                printf("Ошибка чтения значения элемента матрицы\n");
                fprintf(out, "ERROR\n");
                return -1;
            }
            c[i][j] = a[i][j];
        }
    }
    fclose(in);
    
    
    for (i = 0; i < L; i++) {
        rws[i] = 0;
        for (j = 0; j < K; j++) {
            if ((a[i][j] >= M) && (a[i][j] <= N)) {
                rws[i] = 1;
                break;
            }
        }
        //newrw++;
    }
    
    for (j = 0; j < K; j++) {
        cls[j] = 0;
        for (i = 0; i < L; i++) {
            if ((a[i][j] >= M) && (a[i][j] <= N)) {
                cls[j] = 1;
                break;
            }
        }
        //newcl++;
    }
    
    for (i = 0; i < L; i++) {
        if (rws[i] == 0) continue;
        for (j = 0; j < K; j++) {
            check = 0;
            if (cls[j] == 0) continue;
            for (k = 0; k < L; k++) {
                //if (rws[k] == 0) continue;
                for (l = 0; l < j; l++) {
                    if (cls[l] == 0) continue;
                    if (fabs(a[i][j] - c[k][l]) < EPS) {
                        a[i][j] = 1;
                        check = 1;
                        break;
                    }
                }
                if (check == 1) break;
            }
            if (check == 0) a[i][j] = 0;
        }
    }
    
    fprintf(out, "%d %d %d %d\n", M, N, L, K);
    PrintMatrix(a, L, K, out);

    fclose(out);
    FreeMatrix(a, L);
    FreeMatrix(c, L);
    free(cls);
    free(rws);
    return 0;
} 
 */