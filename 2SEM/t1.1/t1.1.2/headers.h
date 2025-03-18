#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <math.h>

double Newton (double xn, double eps, double(*f)(double), double(*df)(double), int *iterations, int *err);
double f0(double x);
double df0(double x);

double f1(double x);
double df1(double x);

double f2(double x);
double df2(double x);

double f3(double x);
double df3(double x);

double f4(double x);
double df4(double x);

#endif