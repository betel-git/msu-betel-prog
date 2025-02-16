#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <math.h>

double Newton (double xn, double eps, double(*f)(double, int), double(*df)(double, int), int i, int *iterations);
double f(double x, int i);
double df(double x, int i);
double ddf(double x, int i);

#endif