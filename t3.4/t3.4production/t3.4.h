#ifndef HEADER
#define HEADER

#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int BinSearch(double arr[], int left, int right, double key);

int BinSearch2(double arr[], int left, int right, double key, int (*cmp)(double, double));

int BinSearch3(void *base, size_t left, size_t right, size_t i, size_t elementSize, void *key, int (*cmp)(const void *, const void *));

void InsertionSortWithBinSearch1(double arr[], int n);

void InsertionSortWithBinSearch2(double arr[], int n);

void InsertionSortWithBinSearch3(void *base, size_t numElements, size_t elementSize, int (*cmp)(const void *, const void *));

double * ReadArrayCnt(FILE *f, size_t *psize, int *errcode);

bool TestSort(int n, double *arr);

int CmpDouble(const void *a, const void *b);

void TextFirst(FILE *inputFile, FILE *outputFile);

void TextSecond(FILE *inputFile, FILE *outputFile);

void TextThird(FILE *inputFile, FILE *outputFile);

#endif