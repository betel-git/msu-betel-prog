#include "headers.h"

double TaylorCos(double x, double eps) {
    int sign = 1, n = 1;
    double temp = 1, sum = 1;

    // Приведение аргумента к диапазону [0, π/2]
    x = fmod(x, 2 * M_PI); // Приведение к интервалу [0, 2π)
    if (x < 0) x = -x; // cos(-x) = cos(x)
    // Определение знака и приведение к интервалу [0, π]
    if (x > M_PI) {
        x -= M_PI;
        sign = -1;
    }
    // Приведение к интервалу [0, π/2] с использованием cos(π - x) = -cos(x)
    if (x > M_PI / 2) {
        x = M_PI - x;
        sign *= -1;
    }
    
    // Непосредственно ряд Тейлора
    while (fabs(temp) >= eps) {
        temp *= -x * x / ((2 * n) * (2 * n - 1));
        sum += temp;
        n++;
    } 
    
    return sign * sum;
}