#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <math.h>

double Bisection (double a, double b, double eps, double(*f)(double, int), int *err, int i, int *iterations);
double f(double x, int i);

#endif