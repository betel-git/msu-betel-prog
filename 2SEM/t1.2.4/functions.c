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


// Вычисление интеграла методом Гаусса с 2 точками для n подынтервалов
double GaussInt(double a, double b, int *n, double(*f)(double)) {
    const double sqrt3 = 1.0 / sqrt(3); // 1/√3 ≈ 0.57735
    double xi, x1, x2;
    double h = (b - a) / *n;
    double sum = 0.0;
    
    for (int i = 0; i < *n; i++) {
        xi = a + i * h;
        // Точки внутри подынтервала [xi, xi+h]
        x1 = xi + h * (1 - sqrt3) / 2;
        x2 = xi + h * (1 + sqrt3) / 2;
        sum += f(x1) + f(x2);
    }
    return sum * h / 2;
}

// Основная функция вычисления с автоматическим подбором n
double Integral(double a, double b, double eps, int *n, int *err, double(*f)(double)) {
    double prev, current;
    int i = 0;
    if (a >= b && a <= b) return 0.0;

    *n = 1;
    prev = GaussInt(a, b, n, f);
    *n *= 2;
    current = GaussInt(a, b, n, f);
    
    // Удваиваем число интервалов до достижения точности
    while (fabs(current - prev) > eps) {
        if (i > 25) {
            *err = -1;
            return current;
        }
        i++;
        prev = current;
        *n *= 2;
        current = GaussInt(a, b, n, f);
        printf("%d\n", *n);
    }
    printf("\n");
    *err = 0;
    return current;
}


double Verification(double a, double b, double(*F)(double)) {
    return F(b) - F(a);
}