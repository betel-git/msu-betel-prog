#include "3.7.h"

int main(void) {
    clock_t t1, t2;
    double seconds;
    double *arr;
    int lst[5] = {1e5, 1e6, 1e7, 2e7, 4e7}; // здесь можно задать размер массивов
    double result[4][5]; // сюда будет записываться время выполнения алгоритма
    srand(time(NULL)); // инициализируем генератор псевдорандомных чисел

    for (int i = 0; i < 5; i++) { // первая реализация
        arr = (double *)malloc(lst[i] * sizeof(double));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = -1e6 + ((1e6 - -1e6) * rand()) / (RAND_MAX + 1.0);
        }
        t1 = clock();
        MergeSortIterative1(arr, lst[i]);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[0][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success 1" : "Failure 1");
        free(arr);
    }

    printf("\n");

    for (int i = 0; i < 5; i++) { // вторая реализация
        arr = (double *)malloc(lst[i] * sizeof(double));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = -1e6 + ((1e6 - -1e6) * rand()) / (RAND_MAX + 1.0);
        }
        t1 = clock();
        MergeSortIterative2(arr, lst[i]);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[1][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success 2" : "Failure 2");
        free(arr);
    }

    printf("\n");

    for (int i = 0; i < 5; i++) { // третья реализация
        arr = (double *)malloc(lst[i] * sizeof(double));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = -1e6 + ((1e6 - -1e6) * rand()) / (RAND_MAX + 1.0);
        }
        t1 = clock();
        MergeSortIterative3(arr, lst[i], sizeof(double), CmpDouble);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[2][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success 3" : "Failure 3");
        free(arr);
    }

    printf("\n");

    for (int i = 0; i < 5; i++) { // реализация qsort
        arr = (double *)malloc(lst[i] * sizeof(double));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = -1e6 + ((1e6 - -1e6) * rand()) / (RAND_MAX + 1.0);
        }
        t1 = clock();
        qsort(arr, lst[i], sizeof(double), CmpDouble);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[3][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success 4" : "Failure 4");
        free(arr);
    }

    printf("\n");

    printf("Насколько близко сложность алгоритма подходит к NlogN: \n");
    printf("NlogN / MlogM = %lf\n", ((4e7 * log10(4e7)) / (2e7 * log10(2e7))));
    printf("sort 1: %lf\n", (result[0][4] / result[0][3]));
    printf("sort 2: %lf\n", (result[1][4] / result[1][3]));
    printf("sort 3: %lf\n", (result[2][4] / result[2][3]));
    printf(" qsort: %lf\n", (result[3][4] / result[3][3]));

   printf("------------------------------------------------------------\n");
   printf("длина |   1e5    |   1e6    |   1e7    |  2e7 (M) |  4e7 (N)\n");
    printf("sort1 | %lf | %lf | %lf | %lf | %lf\n", result[0][0], result[0][1], result[0][2], result[0][3], result[0][4]);
    printf("sort2 | %lf | %lf | %lf | %lf | %lf\n", result[1][0], result[1][1], result[1][2], result[1][3], result[1][4]);
    printf("sort3 | %lf | %lf | %lf | %lf | %lf\n", result[2][0], result[2][1], result[2][2], result[2][3], result[2][4]);
    printf("qsort | %lf | %lf | %lf | %lf | %lf\n", result[3][0], result[3][1], result[3][2], result[3][3], result[3][4]);
    printf("------------------------------------------------------------\n");
    return 0;
}