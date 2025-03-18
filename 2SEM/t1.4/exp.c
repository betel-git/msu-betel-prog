#include "headers.h"

// Быстрое возведение в степень
double MegaPow(double base, int exp) {
    int sign;
    double res;
    if (exp == 0) return 1.0;
    sign = exp < 0 ? -1 : 1;
    exp = abs(exp);
    res = 1.0;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res *= base;
        }
        base *= base;
        exp /= 2;
    }
    return sign == 1 ? res : 1.0 / res;
}


double TaylorExp(double x, double eps) {
    double intx, fracx; // Целая и дробная части x
    double exp_frac = 1.0;
    double temp = 1.0;
    int n = 1;

    if (x < 0) { // Случай с отрицательной степенью
        return 1.0 / TaylorExp(-x, eps);
    }
    fracx = modf(x, &intx);
    
    // Непосредственно ряд Тейлора
    while (fabs(temp) > eps) {
        temp *= fracx / n;
        exp_frac += temp;
        n++;
    }
    return exp_frac * MegaPow(M_E, (int)intx);
}