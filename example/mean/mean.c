#include "mean.h"

int main(void)
{
    double res;
    FILE * f;

    f = fopen("input.txt", "r");
    if (!f) {
        fprintf(stderr, "Error opening data file\n");
        return -1;
    }

    res = CalculateMeanValue(f);

    fprintf(stdout, "Mean value is %f\n", res);
    fclose(f);
    return 0;
}

