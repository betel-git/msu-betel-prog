#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "binary_search.h"
#include "sort.h"
#include "array.h"

bool TestSort(int n, double *arr);
//int CmpDouble(const void *a, const void *b);

bool TestSort(int n, double *arr) {
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        };
    }
    return true;
}

//int CmpDouble(const void *a, const void *b) {
//    const double *pa = (const double *)a;
//   const double *pb = (const double *)b;
//    return (*pa < *pb) ? -1 : (*pa > *pb) ? 1 : 0;
//}

int main(void) {
    FILE *inputFile;
    FILE *outputFile;
    size_t size;
    int errcode;
    double *arr, *arr1;
    char inputFileName[256];
    clock_t t1, t2;
    double seconds;
    double eps = 0.0001;
    int m = 0;
    
    printf("Введите имя входного файла: ");
    scanf("%s", inputFileName);
    
    // открываем выходной файл
    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Error opening output file\n");
        return -1;
    }
    
    // Открываем входной файл
    inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        printf("Error opening input file %s\n", inputFileName);
        return -1;
    }
    
/*     printf("Выберите режим работы (1, 2, 3): ");
    scanf("%s",version); */

    arr = ReadArrayCnt(inputFile, &size, &errcode);
    arr1 = arr;
    t1 = clock();
    InsertionSortWithBinSearch1(arr, size);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time %f\n", seconds);

    // Запись результатов в выходной файл
    fprintf(outputFile, "Название входного файла 1: %s\n", inputFileName);
    for (size_t i = 0; i < size; ++i) {
        fprintf(outputFile, "%.lf\n", arr[i]);
    }

    //arr1 = ReadArrayCnt(inputFile, &size, &errcode);
    t1 = clock();
    InsertionSortWithBinSearch2(arr1, size);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time %f\n", seconds);

    // Запись результатов в выходной файл
    fprintf(outputFile, "Название входного файла 2: %s\n", inputFileName);
    for (size_t i = 0; i < size; ++i) {
        fprintf(outputFile, "%.lf\n", arr1[i]);
    }

    /* arr = ReadArrayCnt(inputFile, &size, &errcode);
    t1 = clock();
    insertion_sort_with_binary_search3(arr, size, sizeof(double), CmpDouble);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time %f\n", seconds); */


    
    printf("%s\n", (TestSort(size, arr)) ? "Success1" : "Failure1");
    printf("%s\n", (TestSort(size, arr1)) ? "Success2" : "Failure2");
    for (size_t i = 0; i < size; ++i) {
        if(fabs(arr[i] - arr1[i]) > eps) {
            m = 1;
        }
    }
    if (m == 1) {
        printf("Failure3");
    }
    else {
        printf("Success3");
    }

    free(arr);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
