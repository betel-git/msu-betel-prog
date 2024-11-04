#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "binary_search.h"
#include "sort.h"
#include "array.h"

bool test_sort(int n, double *arr);

bool test_sort(int n, double *arr) {
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        };
    }
    return true;
}

int CmpDouble(const void *a, const void *b);

int CmpDouble(const void *a, const void *b) {
    const double *pa = (const double *)a;
    const double *pb = (const double *)b;
    return (*pa < *pb) ? -1 : (*pa > *pb) ? 1 : 0;
}

/* int cmp_3(const void *a, const void *b);

int cmp_3(const void *a, const void *b)
{
    const double *ad, *bd;
    
    ad = (const double*)a;
    bd = (const double*)b;
   
    if ((*ad - *bd)<-1e-12) {return -1;}   
    else if ((*ad - *bd)>1e-12) {return 1;}   
    else {return 0;}   
} */

/* int compareDoubles(const void *a, const void *b);
// Функция сравнения для вещественных чисел
int compareDoubles(const void *a, const void *b) {
    double arg1 = *(const double *)a;
    double arg2 = *(const double *)b;
    
    return (arg1 < arg2) ? -1 : (arg1 > arg2) ? 1 : 0;
} */




// третий сценарий работы
int main(void) {
    FILE *inputFile;
    FILE *outputFile;
    size_t size;
    int errcode;
    double *arr;
    char inputFileName[256];
    clock_t t1, t2;
    double seconds;
    int m = 0;
    
    //printf("Введите имя входного файла: ");
    //scanf("%s", inputFileName);
    
    // открываем выходной файл
    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Error opening output file\n");
        return -1;
    }
    
    // Открываем входной файл
    inputFile = fopen(/*inputFileName*/"0.txt", "r");
    if (!inputFile) {
        printf("Error opening input file %s\n", inputFileName);
        return -1;
    }


    arr = ReadArrayCnt(inputFile, &size, &errcode);
    t1 = clock();
    insertion_sort_with_binary_search3(arr, size, sizeof(double), CmpDouble);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time %f\n", seconds);

    // Запись результатов в выходной файл
    //fprintf(outputFile, "Название входного файла 1: %s\n", inputFileName);
    for (size_t i = 0; i < size; ++i) {
        fprintf(outputFile, "%.lf\n", arr[i]);
    }
    
    printf("%s\n", (test_sort(size, arr)) ? "Success1" : "Failure1");
    if (m == 1) {
        printf("Failure3\n");
    }
    else {
        printf("Success3\n");
    }

    free(arr);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
