#ifndef HEADER
#define HEADER
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **FreeMatrix (double **a, int rows);
double **CreateMatrix (int rows, int cols);
void PrintMatrix(double **a, int rows, int cols);
void PrintMatrix2(double **a, int rows, int cols);
int MaxNumberLength(double **a, int rows, int cols);
void GaussianElimination (double **a, int rows, int cols, double eps);
double **GaussianPlusInverse (double **a, int rows, int cols, double eps);
void ConstMultiplication (double **a, int rows, int cols, double c);
double **MatrixMultiplication (double **a, double **b, int m1, int n1, int m2, int n2);
int Rank (double **a, int rows, int cols, double eps);
double Determinant (double **a, int rows, int cols, double eps);
void Solver(double **a, double *x, int n);
void TestRank (FILE *in, double eps, int *err);
void TestDet (FILE *in, double eps, int *err);
void TestSolver (FILE *in, double eps, int *err);
void TestInverse (FILE *in, double eps, int *err);

#endif