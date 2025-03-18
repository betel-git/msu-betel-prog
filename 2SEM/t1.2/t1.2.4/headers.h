#ifndef HEADER
#define HEADER
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

double Verification(double a, double b, double(*F)(double));
double GaussInt(double a, double b, int *n, double(*f)(double));
double Integral(double a, double b, double eps, int *n, int *err, double(*f)(double));
double f1(double x);
double F1(double x);
double f2(double x);
double F2(double x);
double f3(double x);
double F3(double x);
double f4(double x);
double F4(double x);
double f5(double x);
double F5(double x);
double f6(double x);
double F6(double x);
double f7(double x);
double F7(double x);


#endif