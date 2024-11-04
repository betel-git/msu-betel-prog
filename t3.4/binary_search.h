#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int BinSearch(double arr[], int left, int right, double key);

int BinSearch2(double arr[], int left, int right, double key, int (*cmp)(double, double));

int BinSearch3(void *base, size_t left, size_t right, size_t i, size_t elementSize, void *key, int (*comparator)(const void *, const void *));