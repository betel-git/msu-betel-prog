#include <math.h>

int BinSearch(double arr[], int left, int right, double key);

int BinSearch2(double arr[], int left, int right, double key, int (*cmp)(double, double));