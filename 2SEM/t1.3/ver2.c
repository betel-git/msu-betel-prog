#include "headers.h"

double GoldenSearch (double (*f)(double), double a, double b, double eps, int *iter, double *err) {
    double phi = 0.5 * (sqrt(5.0) - 1);
    double x1, x2, f1, f2;
    double x1help, x2help;
    int help = 0;
    *iter = 0;

    x1 = b - phi * (b - a);
    x2 = a + phi * (b - a);
    f1 = f(x1);
    f2 = f(x2);

    while (fabs(b - a) > eps) {
        if (f1 < f2) {
            b = x2;
            x2 = x1;
            f2 = f1;
            x1 = b - phi * (b - a);
            f1 = f(x1);
        }
        else {
            a = x1;
            x1 = x2;
            f1 = f2;
            x2 = a + phi * (b - a);
            f2 = f(x2);
        }

        // Поиск плато
        if (f2 >= f1 && f1 >= f2) {
            help++;
            if (help == 1) {
                x1help = x1;
                x2help = x2;
            }
        }
        else help = 0;
        if (help == 2) {
            *err = fabs(x2help - x1help);
            return (x2help + x1help) / 2; 
        }

        // Ограничитель на количество итераций
        *iter = *iter + 1;
        if (*iter > 1000) break;
    }

    return (a + b) / 2;
}