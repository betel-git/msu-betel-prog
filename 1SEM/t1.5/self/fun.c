#include "lastnumber.h"

// алгоритмическая составляющая очевидна
double Lastnumber (FILE *f, double epsilon, double x) {
    int last_index = 0;
    double y;

    for (int i = 1; fscanf(f, "%lf", &y) == 1; i++) {
        if (fabs(y - x) <= epsilon) {
            last_index = i;
        }
    }

    if (last_index == 0) {
        last_index = -1;
    }

    return last_index;
}