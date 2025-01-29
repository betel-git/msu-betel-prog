#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "greatestsequence.h"

int main(void) {
    FILE *inputFile;
    FILE *outputFile;
    size_t size;
    int errcode;
    int *array;
    int res;
    char inputFileName[256];
    
    printf("Введите имя входного файла: ");
    scanf("%s", inputFileName);
    
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
    
    array = ReadArrayCnt(inputFile, &size, &errcode);
    res = find_max_segment(array, size);

    // Вывод результатов на экран
    printf("Длина самого длинного возрастающего участка: %d\n", res);
    
    // Запись результатов в выходной файл
    fprintf(outputFile, "Длина самого длинного возрастающего участка: %d\n", res);
    fprintf(outputFile, "Название выходного файла: %s", inputFileName);

    free(array);
    fclose(inputFile);
    fclose(outputFile);
    
    return 0;
}
