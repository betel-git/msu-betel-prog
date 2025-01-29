#include "1.h"

// функция подсчёта количества элементов в файле
int Len(FILE *f) {
    int n = 0;
    double x;
    while (fscanf(f, "%lf", &x) == 1) {
        n++;
    }
    if(!feof(f)) {
        return -1;
    }
    rewind(f);
    return n;
}

// функция сканирования элементов из файла в массив
void Scan(FILE *f, double *arr, int n) {
    for (int i = 0; i < n; i++) {
        fscanf(f, "%lf", &arr[i]);
    }
}


/* double Func(double *arr, int n, int k) {
    double max = 0, current = 0;
    int check = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        j = i + 1;
        check = 0;
        while (j < n && check <= k) {
            current = arr[i] + arr[j];
            if (current > max) max = current;
            j++;
            check++;
        }
    }
    return max;
} */

double Func(double *arr, int n, int k) {
    double max = 0, current = 0;
    for (int i = 0; i < n; i++) {
        int check = 0;
        for (int j = i + 1; j < n && check < k; j++, check++) {
            current = arr[i] + arr[j];
            if (current > max) max = current;
        }
    }
    return max;
}