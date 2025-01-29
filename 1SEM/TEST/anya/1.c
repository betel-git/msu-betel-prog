#include <stdio.h>
#include <stdlib.h>

int Len(FILE *f);
void Scan(FILE *f, double *arr, int n);
double Func(double *arr, int n, double k);

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


double Func(double *arr, int n, double k) {
    double max = 0, current = 0;
    for(int i = 0; i < n - 1; i++) {
        //printf("%d\n", i);
        current = arr[i] + arr[i + 1];
        if(current > max && current <= k) {
            max = current;
        }
    }
    return max;
}

int main(void) {
    FILE *in;
    double *a;
    int n;
    double k;
    double res;

    in = fopen("input.txt", "r");
    if(in == NULL) {
        printf("-1\n");
        return -1;
    }
    printf("k: ");
    scanf("%lf", &k);

    n = Len(in);
    a = (double *)malloc(n * sizeof(double));
    Scan(in, a, n);
    
    res = Func(a, n, k);
    printf("Result: %lf\n", res);

    free(a);
    fclose(in);
    return 0;
}