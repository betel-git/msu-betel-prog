#include "headers.h"

double Lagrange(double *x, double *y, int n, double xi) {
    double result = 0.0;
    double temp;

    for (int i = 0; i < n; i++) {
        temp = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                temp = temp * (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += temp;
    }
    return result;
}


double LinearInterpolation(double *x, double *y, int n, double xi) {
    int k = 0;
    double x0, y0, x1, y1;

    while (k < n - 1 && x[k + 1] < xi) k++;
    if (k >= n - 1) return y[n - 1];
    x0 = x[k];
    x1 = x[k + 1];
    y0 = y[k];
    y1 = y[k + 1];

    return y0 + (y1 - y0) * (xi - x0) / (x1 - x0);
}


double QuadraticInterpolation(double *x, double *y, int n, double xi) {
    int k = 0;
    double x0, y0, x1, y1, x2, y2, temp1, temp2, temp3;

    while (k < n - 2 && x[k + 1] < xi) k++;

    x0 = x[k];
    x1 = x[k + 1];
    x2 = x[k + 2];
    y0 = y[k];
    y1 = y[k + 1];
    y2 = y[k + 2];

    temp1 = y0 * ((xi - x1) * (xi - x2)) / ((x0 - x1) * (x0 - x2));
    temp2 = y1 * ((xi - x0) * (xi - x2)) / ((x1 - x0) * (x1 - x2));
    temp3 = y2 * ((xi - x0) * (xi - x1)) / ((x2 - x0) * (x2 - x1));

    return temp1 + temp2 + temp3;
}


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