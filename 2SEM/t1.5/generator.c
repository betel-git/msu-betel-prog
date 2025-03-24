#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double f (double x);
double df (double x);

double f (double x) {
    return x * x * x + 3 * x * x + 3 * x + 3;
}

double df (double x) {
    return 3 * x * x + 6 * x + 3;
}

int main(void) {
    FILE *grid, *megaout;
    double a = -2.5, b = 0.7, c = 5, h = (b - a) / c;
    int i, j;

/*     if ((out = fopen("input.txt", "w"))==NULL) {
        printf("input.txt error\n");
        return -1;
    } */

    if ((grid = fopen("grid.txt", "w"))==NULL) {
        printf("grid.txt error\n");
        return -1;
    }

    if ((megaout = fopen("input.txt", "w"))==NULL) {
        printf("input.txt error\n");
        return -1;
    }

/*     for (i = 0; i <= c; i++) {
        fprintf(out, "%lf %lf\n", a + i * h, f(a + i * h));
    } */

    for (i = 0; i <= c; i++) {
        fprintf(megaout, "%lf %lf %lf\n", a + i * h, f(a + i * h), df(a + i * h));
    }

    h = (b - a) / (c + 2);
    for (j = 0; j <= c + 2; j++) {
        fprintf(grid, "%lf\n", a + j * h);
    }
    printf("success\n");
    return 0;
}