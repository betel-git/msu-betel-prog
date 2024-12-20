#include "1.h"


int NArray(FILE *f) {
    int n = 0;
    int x;
    while(fscanf(f, "%d", &x) == 1){
        n++;
    }
    if(!feof(f)) {
        printf("Error NArray\n");
        return 0;
    }
    rewind(f);
    printf("n: %d\n", n);
    return n;
}


int* ReadArray(FILE *f, int n) {
    int *arr;

    arr = (int *)malloc(n * sizeof(int));
    if(!arr) {
        printf("Malloc Error\n");
        arr = 0;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &arr[i]);
    }
    return arr;
}


int cmp(const void *a, const void *b) {
    int aa = *(int *)a;
    int bb = *(int *)b;
    int res = 0;
    if(aa > bb) {
        res = 1;
    }
    else res = -1;
    return res;
}

int Min(int a, int b) {
    if (a >= b) {
        return a;
    }
    else return b;
}
