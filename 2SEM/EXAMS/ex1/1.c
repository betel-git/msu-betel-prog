#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
double f (double x, double y);
double Bisection (double a, double b, double y, double eps, double(*f)(double, double), int *err);


double f (double x, double y) {
    return -sqrt(x) + y * sin(x);
}

double Bisection (double a, double b, double y, double eps, double(*f)(double, double), int *err) {
    double fa, fb, fc, c;
    fa = f(a, y);
    fb = f(b, y);
    if(fa * fb > 0) {
        *err = 1;
        return 0;
    }

    while(fabs(b - a) > eps) {
        c = (a + b) / 2;
        if(c <= a || c >= b) {
            *err = 2;
            return c;
        }
        fc = f(c, y);
        if(fc <= 0 && fc >= 0) {
            *err = 0;
            return c;
        }
        if(fc * fb < 0) a = c;
        else b = c;
        fa = f(a, y);
        fb = f(b, y);
    }
    *err = 0;
    return c;
}

int main(void) {
    double h, eps;
    double y = 0;
    double res;
    int err = 0;
    FILE *out;
    int k = 0;
    
    if((out = fopen("OUTPUT.txt", "w"))==NULL) {
        printf("OUTPUT.txt error\n");
        return -1;
    }
    
    printf("введите h: \n");
    scanf("%lf", &h);
    printf("введите eps: \n");
    scanf("%lf", &eps);
    while (y <= 100) {
        k = 0;
        while (((M_PI / 2) + 2 * M_PI * k) < y * y) {
            k++;
        }
        k--;
        //k = (int)((M_PI / 2) + 2 * M_PI * k);
        printf("%d\n", k);
        if (k < 0) res = Bisection(0, y * y, y, eps, *f, &err);
        else res = Bisection(((M_PI / 2) + 2 * M_PI * k), y * y, y, eps, *f, &err);
        if (err == 1) printf("error\n");
        fprintf(out, "%lf %lf\n", y, res);
        y = y + h;
    }
    return 0;
}
