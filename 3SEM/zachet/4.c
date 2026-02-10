#include <stdio.h>
#include <math.h>
double Bisection (double a, double b, double A, double eps, int *err);
double f (double x, double a);


double f (double x, double a) {
    return x * exp(-x) - a * exp(a);
}

double Bisection (double a, double b, double A, double eps, int *err) {
    double fa, fb, fc, c;
    fa = f(a, A);
    fb = f(b, A);
    if(fa * fb > 0) {
        *err = 1;
        return 0;
    }
    if(fabs(b - a) <= eps) {
        if((fa <= 0 && fa >= 0)) {
            *err = 3;
            return a;
        }
        else if((fb <= 0 && fb >= 0)) {
            *err = 3;
            return b;
        }
        else {
            *err = 4;
            return 0;
        }
    }

    while(fabs(b - a) > eps) {
        c = (a + b) / 2;
        if(c <= a || c >= b) {
            *err = 2;
            return c;
        }
        fc = f(c, A);
        if(fc <= 0 && fc >= 0) {
            *err = 0;
            return c;
        }
        if(fc * fa < 0) b = c;
        else a = c;
        fa = f(a, A);
        fb = f(b, A);
    }
    *err = 0;
    return c;
}


int main(void) {
    double res;
    double eps = 10e-5;
    int err = 0;
    double a = 2, b = 100;
    double A = 0.1;

    res = Bisection(a, b, A, eps, &err);
    if(err == 0) printf("answer: %.20lf\n", res);
    else if(err == 1) printf("warning: fa * fb > 0\n");
    else if(err == 2) {
        printf("warning: c <= a || c >= b\n");
        printf("answer: %.20lf\n", res);
    }
    else if(err == 3) printf("warning: fabs(b - a) <= eps, but f(a) = 0 or f(b) = 0\n");
    else if(err == 4) printf("warning: fabs(b - a) <= eps\n");

    return 0;
}