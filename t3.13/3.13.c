#include "3.13.h"

int main(void) {
    long long int n;
    long long int m;
    int errcode;
    unsigned int *arr;
    char inputFileName[256];
    FILE *inputFile;
    FILE *outputFile;
    time_t t1, t2;
    double seconds;
    int asceding;
    int bitIndex = 0; // Начальный индекс бита (для unsigned int максимальный бит равен 31)

    printf("Возрастание - 1, убывание - 0: ");
    scanf("%d", &asceding);

    printf("Введите имя входного файла: ");
    scanf("%s", inputFileName);

    // Открываем входной файл
    inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        printf("Error opening input file %s\n", inputFileName);
        return -1;
    }

    // открываем выходной файл
    outputFile = fopen("output.txt", "w");
    if (!outputFile) {
        printf("Error opening output file\n");
        return -1;
    }
    
    arr = ReadArrayCnt(inputFile, &n, &errcode);
    m = n;
    if (errcode != 0) {
        printf("errcode %d\n", errcode);
        return -1;
    }



    
    t1 = clock();
    //QuickBitSort2(n, arr, asceding);
    //-------------------------------------------------------------------------
    while (bitIndex <= 32) {
        QuickBitSort(n, arr, bitIndex, asceding);
        bitIndex++;
        n = m;
    }
    //-------------------------------------------------------------------------
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("seconds %lf\n", seconds);

    for (long long int i = 0; i < n; i++) {
        fprintf(outputFile, "%u\n", arr[i]);
    }

    // аналогично для qsort ------------------------------------------
    arr = ReadArrayCnt(inputFile, &n, &errcode);
    if (errcode != 0) {
        printf("errcode %d\n", errcode);
        return -1;
    }
    t1 = clock();
    qsort(arr, n, sizeof(unsigned int), CmpInt);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("seconds %lf\n", seconds);


    free(arr);
    fclose(outputFile);
    fclose(inputFile);
    return 0;


}
