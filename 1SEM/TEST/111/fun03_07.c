#include "03_07.h"

void Prn(const double *a, int n){
    n = (n > 20) ? 20 : n;
    for(int i = 0; i < n; i++){
        printf("%lf\n", a[i]);
    }
}


void copy(const double *a, double *b, size_t n){
    int k = (int)n;
    for(int i = 0; i < k; i++){
        b[i] = a[i];
    }
}


int Cnt(double *a, int n){
    int cnt = 0;
    for(int i = 0; i < n - 1; i++){
        if(a[i] > a[i + 1]) cnt++;
    }
    return cnt;
}


void Sort1(double *a, int n){
    double *b;
    b = (double *)malloc(n * sizeof(double));
    for(int l = 1; l <= n; l *= 2){
        for(int i = 0; i < n; i+= 2 * l){
            if(i < n - 2 * l){
                Merge_1(a + i, l, a + i + l, l, b + i);
            }
            else if(i < n - l){
                Merge_1(a + i, l, a + i + l, n - (i + l), b + i);
            }
        }
        copy(b, a, n);
    }
    free(b);
}


void Merge_1(double *a, int n, double *b, int m, double *c){
    int i = 0, j = 0, k = 0;
    while(i < n && j < m){
        if(a[i] < b[j]){
            c[k] = a[i];
            i++;
        }
        else{
            c[k] = b[j];
            j++;
        }
        k++;
    }
    if(i < n){
        for(int f = k; f < n + m; f++){
            c[f] = a[i];
            i++;
        }
    }
    else{
        for(int f = k; f < n + m; f++){
            c[f] = b[j];
            j++;
        }
    }
}


void Sort2(double *a, const size_t n, int (*Compare) (double, double)){
    double *b;
    b = (double *)malloc(n * sizeof(double));
    for(size_t l = 1; l <= n; l *= 2){
        for(size_t i = 0; i < n; i+= 2 * l){
            if(i < n - 2 * l){
                Merge_2(a + i, l, a + i + l, l, b + i, (*Compare));
            }
            else if(i < n - l){
                Merge_2(a + i, l, a + i + l, n - (i + l), b + i, (*Compare));
            }
        }
        copy(b, a, n);
    }
    free(b);
}


void Merge_2(double *a, size_t n, double *b, size_t m, double *c, int (*Compare) (double, double)){
    size_t i = 0, j = 0, k = 0;
    while(i < n && j < m){
        if(Compare(a[i], b[j])){
            c[k] = a[i];
            i++;
        }
        else{
            c[k] = b[j];
            j++;
        }
        k++;
    }
    if(i < n){
        for(size_t f = k; f < n + m; f++){
            c[f] = a[i];
            i++;
        }
    }
    else{
        for(size_t f = k; f < n + m; f++){
            c[f] = b[j];
            j++;
        }
    }
}


int Compare(double x, double y){
    if(x < y) return 1;
    return 0;
}



void Sort3(void *a, size_t n, size_t elem_length, int (*cmp) (const void *, const void *)){
    double *b;
    b = (double *)malloc(n * sizeof(double));
    for(size_t l = 1; l < n; l *= 2){
        for(size_t i = 0; i < n; i += 2 * l){
            if(i < n - 2 * l){
                Merge_3(a + i * elem_length, l * elem_length, a + (i + l) * elem_length, l * elem_length, b + i * elem_length, elem_length);
            }
            else if(i < n - l){
                Merge_3(a + i * elem_length, l * elem_length, a + (i + l) * elem_length, (n - (i + l)) * elem_length, b + i * elem_length, elem_length);
            }
            Copy(b, a, n, elem_length);
        }
    }
    free(b);
}


void Merge_3(void *a, size_t n, void *b, size_t m, void *c, size_t elem_length){
    int i = 0, j = 0, k = 0;
    while(i < n && j < m){
        if(cmp((char *)(a + i * elem_length), (char *)(b + j * elem_length))){
            Change_mean(c + k * elem_length, a + i * elem_length, elem_length);
            i++;
        }
        else{
            Change_mean(c + k * elem_length, b + j * elem_length, elem_length);
            j++;
        }
        k++;
    }
    if(i < n){
        for(int f = k; f < n + m; f++){
            Change_mean(c + f * elem_length, a + i * elem_length, elem_length);
            i++;
        }
    }
    else{
        for(int f = k; f < n + m; f++){
            Change_mean(c + f * elem_length, b + j * elem_length, elem_length);
            j++;
        }
    }
}


void Copy(void *a1, void *a2, size_t n, size_t elem_length){
    char *b1 = 0, *b2 = 0;

    for(int j = 0; j < n; j++){
        b1 = (char *)(a1 + j * elem_length);
        b2 = (char *)(a2 + j * elem_length);
        Change_mean(b1, b2, elem_length);
    }
}


int cmp(const void *x, const void *y){
    double a = *(double *)x;
    double b = *(double *)y;
    if(a > b) return 1;
    return 0;
}


void Change_mean(char *a, char *b, int elem_length){ // b -> a
    for(int i = 0; i < elem_length; i++){
        a[i] = b[i];
    }
}


void Change_elem(char *a, char *b, int elem_length){
    char x;
    for(int i = 0; i < elem_length; i++){
        x = a[i];
        a[i] = b[i];
        b[i] = x;
    }
}



