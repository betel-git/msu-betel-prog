#include "03_15.h"

int main(void){
    FILE *f;
    unsigned int *a, *b;
    double t;
    int n;

    printf("Input n: ");
    if(scanf("%d", &n) != 1){
        printf("Error read n\n");
        return -1;
    }
    if(n <= 0){
        printf("Error len array\n");
        return -2;
    }
    
    f = fopen("a", "r");
    if(!f){
        printf("Err open file\n");
        return -3;
    }
    
    a = (unsigned int *)malloc(n * sizeof(unsigned int));
    if(Init(a, n, f) == 0){
            printf("Error read file\n");
            fclose(f);
            return -4;
    }
    printf("Array :\n");
    Prn(a, n);
    b = (unsigned int *)malloc(n * sizeof(unsigned int));
    
    t = clock();
    Radix_4_Bit(a, n, b);
    t = (clock() - t) / CLOCKS_PER_SEC;
    printf("New array : \n");
    Prn(a, n);
    if(Cnt(a, n) > 0) printf("Check array : err sort\n");
    else printf("Check array : OK  Time : %lf\n", t);
    
    free(a);
    fclose(f);
    return 0;
}
