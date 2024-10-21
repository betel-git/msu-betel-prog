#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "fun.h"

int main(void) {
    FILE *inputFile, *outputFile;
    size_t size;
    int errcode;
    double *array;
    char inputFileName[256];

    printf("Введите имя входного файла: ");
    scanf("%s", inputFileName);
    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Ошибка открытия выходного файла\n");
        return -1;
    }

    inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        printf("Ошибка открытия входного файла %s\n", inputFileName);
        return -1;
    }

    array = ReadArrayCnt(inputFile, &size, &errcode);
    MainFunction(array, size);

    for (size_t i = 0; i < size; i++) {
        fprintf(outputFile, "%.f\n", array[i]);
    }

    free(array);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}