#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <math.h>

double Bisection (double a, double b, double eps, double(*f)(double), int *err, int *iterations);
double f0(double x);
double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);

#endif