#include "headers.h"

double f(double x, int i) {
    if(i == 1) return x * x - 2; // TEST 1
    else if(i == 2) return x * x * x; // TEST 2
    else if(i == 3) return sin(x); // TEST 3
    else if(i == 4) return 0.1 * x - 0.25; // TEST 4
    else if(i == 5) return log10(x * x - x); //x * x * x - 2 * x * x + 1; // TEST 5
    else return -1;
}


double Secant (double a, double b, double eps, double(*f)(double, int), int *err, int i, int *iterations) {
    double fa, fb;
    fa = f(a, i);
    fb = f(b, i);
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
        ++*iterations;
        a = a - (b - a) * f(a, i) / (f(b, i) - f(a, i));
        b = b - (a - b) * f(b, i) / (f(a, i) - f(b, i));
    }
    *err = 0;
    return b;
}
