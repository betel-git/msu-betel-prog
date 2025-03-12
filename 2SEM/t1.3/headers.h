#ifndef HEADER
#define HEADER
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double MegaPow(double base, int exp);
double TaylorExp(double x, double eps);
double TaylorSin(double x, double eps);
double TaylorCos(double x, double eps);
double TaylorLog(double x, double eps);

#endif