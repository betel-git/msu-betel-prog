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


double Secant (double a, double b, double eps, double(*f)(double), int *err, int *iterations) {
    double fa, fb;
    fa = f(a);
    fb = f(b);
    if(fa * fb > 0) {
        *err = 1;
        return 0;
    }

    if(fabs(b - a) <= eps) {
        if((fa <= 0 && fa >= 0)) {
            *err = 2;
            return a;
        }
        else if((fb <= 0 && fb >= 0)) {
            *err = 2;
            return b;
        }
        else {
            *err = 3;
            return 0;
        }
    }

    while(fabs(b - a) > eps) {
        if(*iterations > 10000) {
            *err = 4;
            return b;
        }
        ++*iterations;
        fb = f(b);
        fa = f(a);
        if((fb - fa) <= 0 && (fb - fa) >= 0) {
            *err = 5;
            return b;
        }
        a = a - (b - a) * fa / (fb - fa);
        fa = f(a);
        b = b - (a - b) * fb / (fa - fb);
    }
    *err = 0;
    return b;
}
