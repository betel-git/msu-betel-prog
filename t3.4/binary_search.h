#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int binary_search(double arr[], int left, int right, double key);

int binary_search2(double arr[], int left, int right, double key, int (*cmp)(double, double));

int binary_search3(void *base, size_t left, size_t right, size_t i, size_t elementSize, void *key, int (*comparator)(const void *, const void *));