#include "1.h"

int main(void) {
    FILE *in, *out;
    int n;
    double *a;
    double m;

    in = fopen("input.txt", "r");
    if(in == NULL) {
        printf("-1\n");
        return -1;
    }

    out = fopen("output.txt", "w");
    if(out == NULL) {
        printf("-2\n"); fclose(in);
        return -1;
    }

    n = Len(in);

    if(n == 0 || n == -1) {
        printf("-4\n"); fclose(in); fclose(out);
        return -1;
    }

    a = (double *)malloc(n * sizeof(double));
    if(!a) {
        a = 0;
        printf("-5\n"); fclose(in); fclose(out);
        return -1;
    }

    Scan(in, a, n);
    fclose(in);

    m = Mediana(a, n);
    Func(a, n, m);

    for (int i = 0; i < n; i++) {
		fprintf(out, "%.2f\n", a[i]);
	}

    printf("Success\n");
    fclose(out);
    free(a);
    return 0;
}