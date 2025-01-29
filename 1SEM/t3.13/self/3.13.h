#ifndef HEADER
#define HEADER

#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

unsigned int * ReadArrayCnt(FILE *f, int *size, int *errcode);

void Swap(unsigned int* a, unsigned int* b);

bool TestBit(int x, int k);

bool TestSort(int n, unsigned int *arr);

void QuickBitSort(unsigned int *a, int n, bool ascending);

void QuickBitSortRecursive(unsigned int *a, int left, int right, int maxBits, bool ascending);

int QuickBitSortPartition(int n, unsigned int *a, int ibit, bool ascending);

int CmpInt(const void *a, const void *b);

#endif