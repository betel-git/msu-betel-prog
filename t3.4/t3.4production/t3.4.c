#include "t3.4.h"

bool TestSort(int n, double *arr) {
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        };
    }
    return true;
}


int CmpDouble(const void *a, const void *b) {
    const double *pa = (const double *)a;
    const double *pb = (const double *)b;
    return (*pa < *pb) ? -1 : (*pa > *pb) ? 1 : 0;
}


void TextFirst(FILE *inputFile, FILE *outputFile) {
    size_t size;
    int errcode;
    double *arr;
    clock_t t1, t2;
    double seconds;


    arr = ReadArrayCnt(inputFile, &size, &errcode);
    t1 = clock();
    InsertionSortWithBinSearch1(arr, size);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time 1 %f\n", seconds);

    // Запись результатов в выходной файл
    //fprintf(outputFile, "Название входного файла 1: %s\n", inputFileName);
    for (size_t i = 0; i < size; ++i) {
        fprintf(outputFile, "%.lf\n", arr[i]);
    }
    
    printf("%s\n", (TestSort(size, arr)) ? "Success1" : "Failure1");


    free(arr);
}


void TextSecond (FILE *inputFile, FILE *outputFile) {
    size_t size;
    int errcode;
    double *arr;
    clock_t t1, t2;
    double seconds;


    arr = ReadArrayCnt(inputFile, &size, &errcode);
    t1 = clock();
    InsertionSortWithBinSearch2(arr, size);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time 2 %f\n", seconds);

    // Запись результатов в выходной файл
    //fprintf(outputFile, "Название входного файла: %s\n", inputFileName);
    for (size_t i = 0; i < size; ++i) {
        fprintf(outputFile, "%.lf\n", arr[i]);
    }
    printf("%s\n", (TestSort(size, arr)) ? "Success2" : "Failure2");


    free(arr);
}


void TextThird (FILE *inputFile, FILE *outputFile) {
    size_t size;
    int errcode;
    double *arr;
    clock_t t1, t2;
    double seconds;

    arr = ReadArrayCnt(inputFile, &size, &errcode);
    t1 = clock();
    InsertionSortWithBinSearch3(arr, size, sizeof(double), CmpDouble);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time 3 %f\n", seconds);

    // Запись результатов в выходной файл
    //fprintf(outputFile, "Название входного файла: %s\n", inputFileName);
    for (size_t i = 0; i < size; ++i) {
        fprintf(outputFile, "%.lf\n", arr[i]);
    }
    
    printf("%s\n", (TestSort(size, arr)) ? "Success3" : "Failure3");

    free(arr);
}

int main(void) {
    char inputFileName[256];
    FILE *outputFile1, *outputFile2, *outputFile3, *inputFile;
    size_t size;
    int errcode;
    double *arr1, *arr2, *arr3;
    int m = 0;


    printf("Введите имя входного файла: ");
    scanf("%s", inputFileName);

    // открываем выходной файл
    outputFile3 = fopen("output3.txt", "w");
    if (!outputFile3) {
        printf("Error opening output file\n");
        return -1;
    }

    // открываем выходной файл
    outputFile1 = fopen("output1.txt", "w");
    if (!outputFile1) {
        printf("Error opening output file\n");
        return -1;
    }

        // открываем выходной файл
    outputFile2 = fopen("output2.txt", "w");
    if (!outputFile2) {
        printf("Error opening output file\n");
        return -1;
    }
    
    // Открываем входной файл
    inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        printf("Error opening input file %s\n", inputFileName);
        return -1;
    }

    TextFirst(inputFile, outputFile1);
    TextSecond(inputFile, outputFile2);
    TextThird(inputFile, outputFile3);

    arr1 = ReadArrayCnt(outputFile1, &size, &errcode);
    arr2 = ReadArrayCnt(outputFile2, &size, &errcode);
    arr3 = ReadArrayCnt(outputFile3, &size, &errcode);
    for (size_t i = 0; i < size; i++) {
        if (fabs(arr1[i] - arr2[i]) > 1e-6 || fabs(arr1[i] - arr3[i]) > 1e-6 || fabs(arr3[i] - arr2[i]) > 1e-6) {
            m = 1;
            break;
        }
    }
    if (m == 1) {printf("Failure Equals\n");}
    else {printf("Success Equals\n");}
    free(arr1);
    free(arr2);
    free(arr3);
    fclose(outputFile1);
    fclose(outputFile2);
    fclose(outputFile3);
    fclose(inputFile);
    return 0;
}

/* 
// третий сценарий работы
int Main(void) {
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
    InsertionSortWithBinSearch3(arr, size, sizeof(double), CmpDouble);
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("sorting time %f\n", seconds);

    // Запись результатов в выходной файл
    //fprintf(outputFile, "Название входного файла 1: %s\n", inputFileName);
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
 */