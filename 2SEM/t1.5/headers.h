#ifndef HEADER
#define HEADER
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double Lagrange(double *x, double *y, int n, double xi);
double LinearInterpolation(double *x, double *y, int n, double xi);
double QuadraticInterpolation(double *x, double *y, int n, double xi);
double HermiteInterpolation(double *x, double *y, double *dy, int n, double xi);
void LastChance(double *x, double *y, int n, double *a, double *b);

#endif