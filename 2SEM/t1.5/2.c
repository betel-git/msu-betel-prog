#include "headers.h"

double HermiteInterpolation(double *x, double *y, double *dy, int n, double xi) {
    int k = 0;
    double x0, y0, dy0, x1, y1, dy1, t, t2, t3, h00, h10, h01, h11;

    while (k < n - 1 && x[k + 1] < xi) k++;

    x0 = x[k];
    x1 = x[k + 1];
    y0 = y[k];
    y1 = y[k + 1];
    dy0 = dy[k];
    dy1 = dy[k + 1];

    t = (xi - x0) / (x1 - x0);
    t2 = t * t;
    t3 = t2 * t;

    h00 = 2 * t3 - 3 * t2 + 1;
    h10 = t3 - 2 * t2 + t;
    h01 = -2 * t3 + 3 * t2;
    h11 = t3 - t2;

    return h00 * y0 + h10 * (x1 - x0) * dy0 + h01 * y1 + h11 * (x1 - x0) * dy1;
}


void LastChance(double *x, double *y, int n, double *a, double *b) {
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < n; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    *a = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    *b = (sum_y - (*a) * sum_x) / n;
}

int main(void) {
    FILE *in, *grid, *out1, *out2, *out3, *out4, *out5;
    double *a, *b, *c, *d;
    size_t m = 0, n = 0;
    //int err;
    double res;
    double temp_a, temp_b, temp_c, temp_d;
    double r, s;

    if ((in = fopen("input.txt", "r"))==NULL) {
        printf("input.txt error\n");
        return -1;
    }

    if ((grid = fopen("grid.txt", "r"))==NULL) {
        printf("grid.txt error\n");
        return -1;
    }

    if ((out1 = fopen("out1.txt", "w"))==NULL) {
        printf("out1.txt error\n");
        return -1;
    }

    if ((out2 = fopen("out2.txt", "w"))==NULL) {
        printf("out2.txt error\n");
        return -1;
    }

    if ((out3 = fopen("out3.txt", "w"))==NULL) {
        printf("out3.txt error\n");
        return -1;
    }

    if ((out4 = fopen("out4.txt", "w"))==NULL) {
        printf("out4.txt error\n");
        return -1;
    }

    if ((out5 = fopen("out5.txt", "w"))==NULL) {
        printf("out5.txt error\n");
        return -1;
    }


    while (fscanf(in, "%lf %lf %lf", &temp_a, &temp_b, &temp_d) == 3) n++;

    rewind(in);

    a = (double *)malloc(n * sizeof(double));
    b = (double *)malloc(n * sizeof(double));
    d = (double *)malloc(n * sizeof(double));

    for (size_t i = 0; i < n && fscanf(in, "%lf %lf %lf", &a[i], &b[i], &d[i]) == 3; i++);


    while (fscanf(grid, "%lf", &temp_c) == 1) m++;

    rewind(grid);

    c = (double *)malloc(m * sizeof(double));

    for (size_t i = 0; i < m; i++) fscanf(grid, "%lf", &c[i]);

    fclose(grid);


    // Вычисление и вывод интерполированных значений
    for (size_t i = 0; i < m; i++) {
        res = Lagrange(a, b, n, c[i]);
        fprintf(out1, "%lg %lg\n", c[i], res);
    }
    for (size_t i = 0; i < m; i++) {
        res = LinearInterpolation(a, b, n, c[i]);
        fprintf(out2, "%lg %lg\n", c[i], res);
    }
    for (size_t i = 0; i < m; i++) {
        res = QuadraticInterpolation(a, b, n, c[i]);
        fprintf(out3, "%lg %lg\n", c[i], res);
    }
    for (size_t i = 0; i < m; i++) {
        res = HermiteInterpolation(a, b, d, n, c[i]);
        fprintf(out4, "%lg %lg\n", c[i], res);
    }
    LastChance(a, b, n, &r, &s);
    for (size_t i = 0; i < m; i++) {
        res = r * c[i] + s;
        fprintf(out5, "%lg %lg\n", c[i], res);
    }

    fclose(out1), fclose(out2), fclose(out3), fclose(out4);
    free(a), free(b), free(c);
    printf("success\n");
    return 0;
}