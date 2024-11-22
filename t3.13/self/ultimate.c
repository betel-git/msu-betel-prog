#include "3.13.h"

int main(void) {
    clock_t t1, t2;
    double seconds;
    unsigned int *arr;
    int min = 0, max = 32000;
    //int ascending = 1;
    int lst[5] = {1e5, 1e6, 1e7, 4e7, 8e7}; // здесь можно задать размер массивов
    double result[2][5]; // сюда будет записываться время выполнения алгоритма
    srand(time(NULL)); // инициализируем генератор псевдорандомных чисел
    

    for (int i = 0; i < 5; i++) { // первая реализация
        arr = (unsigned int *)malloc(lst[i] * sizeof(unsigned int));
        for (int j = 0; j < lst[i]; j++) {
            arr[i] = min + (rand() % (max - min + 1));
        }
        t1 = clock();
        QuickBitSort(arr, lst[i], true);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[0][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success" : "Failure");
        free(arr);
    }

    printf("\n");

    for (int i = 0; i < 5; i++) { // реализация qsort
        arr = (unsigned int *)malloc(lst[i] * sizeof(unsigned int));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = min + (rand() % (max - min + 1));
        }
        t1 = clock();
        qsort(arr, lst[i], sizeof(unsigned int), CmpInt);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[1][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success" : "Failure");
        free(arr);
    }


    printf("Насколько близко сложность алгоритма подходит к NlogN: \n");
    printf("NlogN / MlogM = %lf\n", ((8e7 * log10(8e7)) / (4e7 * log10(4e7))));
    printf("sort 1: %lf\n", (result[0][4] / result[0][3]));
    printf("qsort: %lf\n", (result[1][4] / result[1][3]));

   printf("------------------------------------------------------------\n");
   printf("длина |   1e5    |   1e6    |   1e7    |   4e7    |   8e7\n");
    printf("sort1 | %lf | %lf | %lf | %lf | %lf\n", result[0][0], result[0][1], result[0][2], result[0][3], result[0][4]);
    printf("qsort | %lf | %lf | %lf | %lf | %lf\n", result[1][0], result[1][1], result[1][2], result[1][3], result[1][4]);
    return 0;
}