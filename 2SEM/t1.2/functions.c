#include "headers.h"

double f(double x, int i) {
    if(i == 1) return x * x - 2; // TEST 1
    else if(i == 2) return x * x * x; // TEST 2
    else if(i == 3) return sin(x); // TEST 3
    else if(i == 4) return 0.1 * x - 0.25; // TEST 4
    else if(i == 5) return x * x * x - 2 * x * x + 1; // TEST 5
    else return -1;
}


double df(double x, int i) {
    if(i == 1) return 2 * x;
    else if(i == 2) return 3 * x * x;
    else if(i == 3) return cos(x);
    else if(i == 4) return 0.1;
    else if(i == 5) return 3 * x * x - 4 * x;
    else return -1;
}


double ddf(double x, int i) {
    if(i == 1) return 2;
    else if(i == 2) return 6 * x;
    else if(i == 3) return -sin(x);
    else if(i == 4) return 0;
    else if(i == 5) return 6 * x - 4;
    else return -1;
}


double Newton (double xn, double eps, double(*f)(double, int), double(*df)(double, int), int i, int *iterations) {
    double x1 = xn - f(xn, i) / df(xn, i);
    double x0 = xn;
    while(fabs(x0 - x1) > eps) {
        ++*iterations;
        x0 = x1;
        x1 = x1 - f(x1, i) / df(x1, i);
    }
    return x1;
}