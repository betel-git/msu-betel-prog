#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fun.h"

int main(void) {
    FILE *outputFile;
    int n, m;
    int *arr;

    printf("Введите число N: ");
    scanf("%d", &n);
    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Ошибка открытия выходного файла\n");
        return -1;
    }
    // биномиальных коэффициентов на 1 больше, чем n
    m = n + 1;
    // создаём массив и проверяем его
    arr = (int*)malloc((m)*sizeof(int));
    if (!arr) {
       printf("Memory allocation error\n");
        return -1;
    }
    // Непосредственно функция алгоритма
    Pascal(arr, n);
    // запись значений в выходной файл
    for (int i = 0; i < m; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }
    // освобождение памяти
    free(arr);
    fclose(outputFile);
    return 0;
}