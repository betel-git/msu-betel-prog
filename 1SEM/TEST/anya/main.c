#include "1.h"

int main(void) {
    FILE *in;
    double *a;
    int n;
    int k;
    double res;

    in = fopen("input.txt", "r");
    if(in == NULL) {
        printf("-1\n");
        return -1;
    }
    printf("k: ");
    scanf("%d", &k);

    n = Len(in);
    a = (double *)malloc(n * sizeof(double));
    Scan(in, a, n);
    
    res = Func(a, n, k);
    printf("Result: %lf\n", res);

    free(a);
    fclose(in);
    return 0;
}