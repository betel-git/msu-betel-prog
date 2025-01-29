#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void InsertionSortWithBinSearch1(double arr[], int n);

void InsertionSortWithBinSearch2(double arr[], int n);

void InsertionSortWithBinSearch3(void *base, size_t numElements, size_t elementSize, int (*comparator)(const void *, const void *));