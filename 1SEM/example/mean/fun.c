#include "mean.h"

double CalculateMeanValue (FILE *f)
{
    double sum = 0, a;
    int n;
    for (n = 0; fscanf(f, "%lf", &a) == 1; ++n) {
        sum += a;
    }
    if (n != 0) { sum /= n; }
    return sum;
}
