#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include "binary_search.h"
#include "sort.h"
#include "array.h"

bool TestSort(int n, double *arr);

bool TestSort(int n, double *arr) {
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        };
    }
    return true;
}

// первый сценарий работы
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


    arr = ReadArrayCnt(inputFile, &size, &errcode);
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
    
    printf("%s\n", (TestSort(size, arr)) ? "Success1" : "Failure1");
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
