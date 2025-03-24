#ifndef HEADER
#define HEADER
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//double ParabolicSearch(double (*f)(double), double x1, double x2, double eps, int *iter);
//double GoldenSearch (double (*f)(double), double a, double b, double eps, int *iter, double *err);
double ParabolicGeometry(double (*f)(double), double x1, double x3, double eps, int *iter, double *err);
double ParabolicGrid(double (*f)(double), double x1, double x3, double eps, int *iter, double *err);
double ParabolicGolden(double (*f)(double), double x1, double x3, double eps, int *iter, double *err);
double f1(double x);
double f2(double x);
double f3(double x);

#endif