#ifndef HEADER
#define HEADER

#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int CmpDouble(const void *a, const void *b);

bool TestSort(int n, double *arr);

void Merge1(double arr[], int left, int mid, int right, double temp[]);

void Merge2(double arr[], int left, int mid, int right, double temp[]);

void Merge3(void* arr, int left, int mid, int right, size_t elem_size, int (*cmp)(const void *, const void *));

void MergeSortIterative1(double arr[], int n);

void MergeSortIterative2(double arr[], int n);

void MergeSortIterative3(void *arr, int n, size_t elementSize, int(*cmp)(const void *, const void *));

double * ReadArrayCnt(FILE *f, size_t *size, int *errcode);

void TextFirst(FILE *inputFile, FILE *outputFile);

void TextSecond(FILE *inputFile, FILE *outputFile);

void TextThird(FILE *inputFile, FILE *outputFile);

int Compare(double a, double b);


#endif