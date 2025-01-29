#include "1.h"

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