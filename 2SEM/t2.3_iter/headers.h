#ifndef HEADER
#define HEADER
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int SimpleIteration (double** A, double* b, double* x, int n, double alpha, double eps, int max_iter, int test);
double **CreateMatrix (int rows, int cols);
double **FreeMatrix (double **a, int rows);
void Matrix_x_Vector (double** A, double* x, double* result, int n);
double VectorNorm (double* v, int n);
double **Test1 (int n);
void Plot (const char* filename, int test);
double ScalarProduct (double* a, double* b, int n);
int SpeedestDescent (double** A, double* b, double* x, int n, double epsilon, int max_iter, int test);
int GaussSeidel (double** A, double* b, double* x, int n, double epsilon, int max_iter, int test);


#endif