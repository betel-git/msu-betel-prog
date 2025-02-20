#include "headers.h"

double f0(double x) {
    return exp(x) - 1e-10;
}

double f1(double x) {
    return tan(x) - 1234567;
}

double f2(double x) {
    return x * x * x * x - 1e-16;
}

double f3(double x) {
    return sin(x);
}

double f4(double x) {
    return x * x * x;
}



double Bisection (double a, double b, double eps, double(*f)(double), int *err, int *iterations) {
    double fa, fb, fc, c;
    fa = f(a);
    fb = f(b);
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
        ++*iterations;
        c = (a + b) / 2;
        if(c <= a || c >= b) {
            *err = 2;
            return c;
        }
        fc = f(c);
        if(fc <= 0 && fc >= 0) {
            *err = 0;
            return c;
        }
        if(fc * fa < 0) b = c;
        else a = c;
        fa = f(a);
        fb = f(b);
    }
    *err = 0;
    return c;
}
