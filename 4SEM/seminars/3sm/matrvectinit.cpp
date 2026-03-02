
#include <cstdlib>
#include <cmath>
#include "matrvectinit.h"

double * InitMatrix(unsigned nrows, unsigned ncols)
{
    double *matr = (double*)malloc(nrows*ncols*sizeof(double));
    if (!matr) return nullptr;
    for (unsigned i=0; i<nrows*ncols; i++) {
        matr[i] = double(rand())/RAND_MAX * 10.0 - 5.0;
        matr[i] = int(matr[i]);
    }
    return matr;
}

double * InitVector(unsigned n, bool fill)
{
    double *vect = (double*)malloc(n*sizeof(double));
    if (!vect) return nullptr;
    if (fill) {
        for (unsigned i=0; i<n; i++) {
            vect[i] = double(rand())/RAND_MAX * 20.0 - 10.0;
            vect[i] = int(vect[i]);
        }
    }
    return vect;
}

void  PrintMatrix(FILE *f, double *matr, unsigned nrows, unsigned ncols, const char *text)
{
    if (!f) return;
    if (text) { fprintf(f, "%s", text); }
    for (unsigned i = 0; i < nrows; i++) {
        for (unsigned j = 0; j < ncols; j++) {
            fprintf(f, " %10.4f",matr[i*ncols + j]);
        }
        fputc('\n', f);
    }
}



void  PrintVector(FILE *f, double *vect, unsigned n, const char *text)
{
    if (!f) return;
    if (text) { fprintf(f, "%s", text); }
    for (unsigned i = 0; i < n; i++) {
        fprintf(f, " %10.4f",vect[i]);
    }
    fputc('\n', f);
}

void  TestVect(unsigned n, double *v1, double *v2)
{
    double d, m = 0;
    for (unsigned i=0; i<n; i++) {
        d = fabs(v1[i] - v2[i]);
        if (m < d) { m = d; }
    }
    printf("TestVext  max diff %e\n", m);
}



