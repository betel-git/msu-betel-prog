#include <stdio.h>
#include <math.h>

double Bissection (double a, double b, double eps, double(*f)(double), int err);
double Newton (double x0, double eps, double(*f)(double), double(*df)(double), int *err);
double f(double x);
double df(double x);


double f(double x) {
    double c;
    c = x * x - 2;
    return c;
}


double df(double x) {
    double c;
    c = 2 * x;
    return c;
}


double Bissection (double a, double b, double eps, double(*f)(double), int err) {
    double fa, fb, fc, c;
    fa = f(a);
    fb = f(b);
    if (fa * fb > 0) {
        err = 1;
        return 0;
    }
    printf("check\n");
    while(fabs(b - a) > eps) {
        c = (a + b) / 2;
        if(c <= a || c >= b) {
            err = 2;
            return c;
        }
        fc = f(c);
        if(fc <= 0 && fc >= 0) {
            err = 0;
            return c;
        }
        if(fc * fa < 0) b = c;
        else a = c;
        fa = f(a);
        fb = f(b);
        printf("%lf\n", c);
    }
    err = 0;
    return c;
}


/* double Newton (double x0, double eps, double(*f)(double), double(*df)(double), int *err) {
    double d;
    while() {
        x0 = x0 - (f(x0) / df(x0));
    }
    while(fabs(d) > eps / 2) {
        d = f(x0) / df(x0);
        x0 = x0 - d;
    }
} */


int main() {
    double res;
    double eps = 0.001;
    int err = 0;
    res = Bissection(-1, 3, eps, *f, err);
    printf("%lf\n", res);
    return 0;
}

