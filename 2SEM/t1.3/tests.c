#include "headers.h"


double f1 (double x) {
    return (x - 1) * (x - 1) * (x - 1) * (x - 1); // x = 1 fx = 0
}


double f2 (double x) {
    return (x - 1) * (x - 1) * (x - 1) * (x - 1) + 1; // x = 1 fx = 1
}


double f3 (double x) {
    return pow(x - 2.5, 4) + 3*pow(x - 1, 2); // x = 1.5577 fx = 1.7215
}