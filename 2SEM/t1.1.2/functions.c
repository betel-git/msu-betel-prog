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


double df0(double x) {
    return exp(x);
}

double df1(double x) {
    return 1 / (cos(x) * cos(x));
}

double df2(double x) {
    return 4 * x * x * x;
}

double df3(double x) {
    return cos(x);
}

double df4(double x) {
    return 3 * x * x;
}


double Newton (double xn, double eps, double(*f)(double), double(*df)(double), int *iterations, int *err) {
    double x1, x0 = xn;
    double dfx = df(xn), fx = f(xn);
    if(dfx >= 0 && dfx <= 0) {
        *err = 1;
        return 0;
    }
    x1 = xn - fx / dfx;
    while(fabs(x0 - x1) > eps) {
        if(*iterations > 10000) {
            *err = 2;
            return x1;
        }
        ++*iterations;
        if(dfx >= 0 && dfx <= 0) {
            *err = 1;
            return x1;
        }
        x0 = x1;
        fx = f(x1);
        dfx = df(x1);
        x1 = x1 - fx / dfx;
    }
    *err = 0;
    return x1;
}