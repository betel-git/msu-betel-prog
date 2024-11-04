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


int main(void) {
    clock_t t1, t2;
    double seconds;
    double *arr;
    int lst[5] = {1e3, 1e4, 4e4, 1e5, 4e5};
    double result[3][5];
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        arr = (double *)malloc(lst[i] * sizeof(double));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = -1e6 + ((1e6 - -1e6) * rand()) / (RAND_MAX + 1.0);
        }
        t1 = clock();
        InsertionSortWithBinSearch1(arr, lst[i]);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[0][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success" : "Failure");
        free(arr);
    }
    for (int i = 0; i < 5; i++) {
        arr = (double *)malloc(lst[i] * sizeof(double));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = -1e6 + ((1e6 - -1e6) * rand()) / (RAND_MAX + 1.0);
        }
        t1 = clock();
        InsertionSortWithBinSearch2(arr, lst[i]);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[1][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success" : "Failure");
        free(arr);
    }
    for (int i = 0; i < 5; i++) {
        arr = (double *)malloc(lst[i] * sizeof(double));
        for (int j = 0; j < lst[i]; j++) {
            arr[j] = -1e6 + ((1e6 - -1e6) * rand()) / (RAND_MAX + 1.0);
        }
        t1 = clock();
        InsertionSortWithBinSearch3(arr, lst[i], sizeof(double), CmpDouble);
        t2 = clock();
        seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
        result[2][i] = seconds;
        printf("%s\n", (TestSort(lst[i], arr)) ? "Success" : "Failure");
        free(arr);
    }
/*     for (int i = 0; i < 3; i++){
        for (int j = 0; j < 5; j++) {
            printf("%lf\n", result[i][j]);
        }
    } */


   printf("------------------------------------------------------------\n");
   printf("длина | 1e3 | 1e4 | 4e4 | 1e5 | 4e5\n");
    printf("sort1 | %lf | %lf | %lf | %lf | %lf\n", result[0][0], result[0][1], result[0][2], result[0][3], result[0][4]);
    printf("sort2 | %lf | %lf | %lf | %lf | %lf\n", result[1][0], result[1][1], result[1][2], result[1][3], result[1][4]);
    printf("sort3 | %lf | %lf | %lf | %lf | %lf\n", result[2][0], result[2][1], result[2][2], result[2][3], result[2][4]);
    return 0;
}