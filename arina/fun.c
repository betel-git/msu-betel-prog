#include "1.h"

int Len(FILE *f) {
    int n = 0;
    double x;
    while(fscanf(f, "%lf", &x) == 1) {
        n++;
    }
    if(!feof(f)){
        return -1;
    }
    rewind(f);
    return n;
}


void Scan(FILE *f, double *a, int n) {
    for (int i = 0; i < n; i++) {
        fscanf(f, "%lf", &a[i]);
    }
}

double Mediana(double *a, int n) {
    double x = 0;
    double res = 0;
    for(int i = 0; i < n; i++) {
        x += a[i];
    }
    res = x / n;
    return res;
}

void Func(double *a, int n, double m) {
    double temp;
    int check = 1;
    while (check != 0) {
        for(int i = 0; i < n - 1; i++) {
            if (fabs(a[i] - m) > fabs(a[i + 1] - m)) {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
        check = 0;
        for (int j = 0; j < n - 1; j++) {
            if (fabs(a[j] - m) > fabs(a[j + 1] - m)) {
                check = 1;
                break;
            }
        }
    }
}