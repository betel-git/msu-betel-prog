#include <math.h>

int binary_search(double arr[], int left, int right, double key);

int binary_search2(double arr[], int left, int right, double key, int (*cmp)(double, double));