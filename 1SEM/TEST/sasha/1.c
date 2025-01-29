#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Len(FILE *f);
void Scan(FILE *f, double *arr, int n);
double Func(double *arr, int n);

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


double Func(double *arr, int n) {
    int count = 2;
    int max = 2;
    double eps = 0.000001;
    double delta = arr[1] - arr[0], delta_temp = arr[1] - arr[0];
    if (n == 1) return 1;
    if (n == 2) return 2;
    for (int i = 0; i < n - 1; i++) {
        delta = arr[i + 1] - arr[i];
        if (fabs(delta - delta_temp) < eps) {
            count++;
        }
        else {
            if(count > max) {
                max = count;
                count = 2;
            }
        }
        delta_temp = delta;
    }
    if (count > max) return count;
    else return max;
}

int main(void) {
    FILE *in;
    double *a;
    int n;
    int res;

    in = fopen("input.txt", "r");
    if(in == NULL) {
        printf("-1\n");
        return -1;
    }

    n = Len(in);
    a = (double *)malloc(n * sizeof(double));
    Scan(in, a, n);
    
    res = Func(a, n);
    printf("Result: %d\n", res);

    free(a);
    fclose(in);
    return 0;
}