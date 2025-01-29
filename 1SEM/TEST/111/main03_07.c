#include "03_07.h"

int main(void){
    double *a, *b1, *b2, *b3;
    FILE *f;
    int n = 100;
    size_t k = 1000;
    double t;

    f = fopen("a", "r");
    if(!f){
        printf("ERR open");
        return -1;
    }

    a = (double *)malloc((n) * sizeof(double));
    
    for(int i = 0; i < n; i++){
        if(!(fscanf(f, "%lf", a + i))){
            printf("ERR read");
            free(a);
            fclose(f);
            return -2;
        }
    }
    fclose(f);

    b1 = (double *)malloc(n * sizeof(double));
    b2 = (double *)malloc(k * sizeof(double));
    b3 = (double *)malloc(k * sizeof(double));

    copy(a, b1, n);

    t = clock();
    Sort1(b1, n);
    t = (clock() - t) / CLOCKS_PER_SEC;

    if(Cnt(b1, n) == 0) printf("Sort1 : %lf\n\n", t);
    else printf("Sort1 : ERR cnt != 0\n\n");
    
    
    copy(a, b2, k);

    t = clock();
    Sort2(b2, k, (*Compare));
    t = (clock() - t) / CLOCKS_PER_SEC;
    if(Cnt(b2, (int)k) == 0) printf("Sort2 : %lf\n", t);
    else printf("Sort2 : ERR cnt != 0\n");
    

    copy(a, b3, n);

    t = clock();
    Sort3(b3, k, sizeof(double), (*cmp));
    t = (clock() - t) / CLOCKS_PER_SEC;
    if(Cnt(b3, n) == 0) printf("Sort3 : %lf\n", t);
    else printf("Sort3 : ERR cnt != 0\n");

    free(a);
    free(b1);
    free(b2);
    free(b3);
    return 0;
}
