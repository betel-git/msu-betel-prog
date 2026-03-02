
#pragma once
#include <cstdio>

double * InitMatrix(unsigned nrows, unsigned ncols);
double * InitVector(unsigned n, bool fill = false);
void  PrintMatrix(FILE *f, double *matr, unsigned nrows, unsigned ncols, const char *text = nullptr);
void  PrintVector(FILE *f, double *vect, unsigned n, const char *text = nullptr);
void  TestVect(unsigned n, double *v1, double *v2);

