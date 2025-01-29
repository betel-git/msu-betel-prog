/* Содержание:
1. Функция для подсчёта элементов массива
2. Функция для сканирования файла и переноса данных в массив
3. Функция сравнения для qsort */

#include "autotest.h"


int NArray(FILE *f) {
    int n = 0;
    double x;
    while(fscanf(f, "%lf", &x) == 1){
        n++;
    }
    if(!feof(f)) {
        printf("Error NArray\n");
        return 0;
    }
    rewind(f);
    printf("n: %d\n", n);
    return n;
}


double* ReadArray(FILE *f, int n) {
    double *arr;

    arr = (double *)malloc(n * sizeof(double));
    if(!arr) {
        printf("Malloc Error\n");
        arr = 0;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fscanf(f, "%lf", &arr[i]);
    }
    return arr;
}


int cmp(const void *a, const void *b) {
    double aa = *(double *)a;
    double bb = *(double *)b;
    int res = 0;
    if(aa > bb) {
        res = 1;
    }
    else res = -1;
    return res;
}