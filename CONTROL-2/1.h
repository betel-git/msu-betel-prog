#ifndef A_H
#define A_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int NArray (FILE *f);
int* ReadArray(FILE *f, int n);
int cmp(const void *a, const void *b);
int Min(int a, int b);

#endif
