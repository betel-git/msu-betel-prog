#include "headers.h"

double f1(double x) {
    return sin(1000 * x);
}

double F1(double x) {
    return -0.001 * cos(x);
}


double f2(double x) {
    return exp(- x * x);
}

double F2(double x) {
    x = x + 0;
    return 12345;
}


double f3(double x) {
    return tanh(100 * x);
}

double F3(double x) {
    return 0.01 * log(cosh(100 * x));
}


double f4(double x) {
    return sin(x) + sin(10 * x) + sin(100 * x);
}

double F4(double x) {
    return -cos(x) - 0.1 * cos(10 * x) - 0.01 * cos(100 * x);
}


double f5(double x) {
    return sin(x) + 0.01 * sin(1000 * x);
}

double F5(double x) {
    return -cos(x) + 0.00001 * sin(1000 * x);
}


double f6(double x) {
    if (fabs(x) > 1e-15 && fabs(x) < 1) return 1 / sqrt(1 - (x * x));
    else return 0;
}

double F6(double x) {
    if (fabs(x) < 1) return asin(x);
    else return 0;
}


double f7(double x) {
    return exp(-x) * sin(1000 * x);
}

double F7(double x) {
    return -pow(M_E, -x) * (sin(1000 * x) + 1000 * cos(1000 * x)) / (1 + 1000 * 1000);
}

// Вычисление интеграла методом трапеций (по усовершенствованной формуле Котеса)
double TrapezoidInt(double a, double b, int *n, double(*f)(double)) {
    double h, sum, x;
    h = (b - a) / *n;
    sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < *n; i++) {
        x = a + i * h;
        sum += f(x);
    }
    
    return sum * h;
}

// Основная функция вычисления с автоматическим подбором n
double Integral(double a, double b, double eps, int *n, int *err, double(*f)(double)) {
    int i = 0;
    double prev, current;
    if (a >= b && a <= b) return 0.0;
    
    *n = 1; // Начальное количество отрезков
    prev = TrapezoidInt(a, b, n, f);
    *n *= 2;
    current = TrapezoidInt(a, b, n, f);
    
    // Итеративное удвоение n до достижения точности
    while (fabs(current - prev) > eps) {
        if (i > 25) {
            *err = -1;
            return current;
        }
        i++;
        prev = current;
        *n *= 2;
        current = TrapezoidInt(a, b, n, f);
        printf("%d\n", *n);
    }
    printf("\n");
    *err = 0;
    return current;
}

// Формула Ньютона-Лейбница
double Verification(double a, double b, double(*F)(double)) {
    return F(b) - F(a);
}