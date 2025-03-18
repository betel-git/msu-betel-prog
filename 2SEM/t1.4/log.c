#include "headers.h"

double TaylorLog(double x, double eps) {
    double r = x, y, y_squared, sum, temp;
    int m = 0, n = 1;

    // Проверка на положительность
    if (x <= 0) {
        return NAN;
    }
    
    // Приведение аргумента к диапазону [1/e, e]
    while (r < 1.0 / M_E) {
        r *= M_E;
        m--;
    }
    while (r >= M_E) {
        r /= M_E;
        m++;
    }
    
    // Вычисление y = (1 - r)/(1 + r) для использования ряда
    y = (1.0 - r) / (1.0 + r);
    y_squared = y * y;
    sum = y;
    temp = y;

    // Непосредственно ряд Тейлора
    while (fabs(temp) >= eps) {
        temp *= y_squared;
        temp *= (double)(2 * n - 1) / (double)(2 * n + 1);
        sum += temp;
        n++;
    } 
    
    return m - 2 * sum; // ln(x) = m + ln(r), где ln(r) = -2*sum
}
