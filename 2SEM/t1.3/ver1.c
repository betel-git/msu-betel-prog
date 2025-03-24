#include "headers.h"

// Функция для поиска минимума методом параболы
double ParabolicSearch(double (*f)(double), double x1, double x3, double eps, int *iter) {
    double x2 = (x1 + x3) / 2.0; // Средняя точка
    double f1 = f(x1), f2 = f(x2), f3 = f(x3);
    double xp, fp;
    double A, B, a, b;
    int i;
    double alpha;

    for (i = 0; i < 100; i++) {
        //printf("%.15lg %.15lg %.15lg\n", x1, x2, x3);
        // Коэффициенты параболы ax^2 + bx + c
        A = x1 * (f2 - f3) + x2 * (f3 - f1) + x3 * (f1 - f2);
        B = (x1 * x1) * (f2 - f3) + (x2 * x2) * (f3 - f1) + (x3 * x3) * (f1 - f2);
        a = B / (2 * A);
        b = ((x1 * x1 - x2 * x2) * (f2 - f3) + (x2 * x2 - x3 * x3) * (f3 - f1)) / (2 * A);
    
        // Вершина параболы
        xp = -b / (2 * a);
        fp = f(xp);

        // Обновление точек
        if (xp < x2) {
            if (fp < f2) {
                x3 = x2; f3 = f2;
                x2 = xp; f2 = fp;
            } 
            else {
                x1 = xp; f1 = fp;
            }
        } 
        else {
            if (fp < f2) {
                x1 = x2; f1 = f2;
                x2 = xp; f2 = fp;
            } 
            else {
                x3 = xp; f3 = fp;
            }
        }

        // Измельчение интервала с помощью геометрической прогрессии
        if (fabs(x3 - x1) > eps) {
            alpha = 0.5; // Коэффициент измельчения
            x1 = x2 - alpha * (x2 - x1);
            x3 = x2 + alpha * (x3 - x2);
            f1 = f(x1);
            f3 = f(x3);
        }
        else break;
    }
/*     for (i = 0; i < 100; i++) {
        printf("%.15le %.15le %.15le\n", x1, x2, x3);
        // Коэффициенты параболы ax^2 + bx + c
        a = (f3 - (x3 * (f2 - f1) + x2 * f1 - x1 * f2) / (x2 - x1)) / (x3 * (x3 - x1 - x2) + x1 * x2);
        b = ((f2 - f1) / (x2 - x1)) - a * (x1 + x2);
        c = ((x2 * f1 - x1 * f2) / (x2 - x1)) + a * x1 * x2;
    
        // Вершина параболы
        xp = -b / (2 * a);
        printf("xp: %.15le\n", xp);
        fp = a * xp * xp + b * xp + c;
        
        // Обновление точек
        if (xp < x2) {
            if (fp < f2) {
                x3 = x2; f3 = f2;
                x2 = xp; f2 = fp;
            } 
            else {
                x1 = xp; f1 = fp;
            }
        } 
        else {
            if (fp < f2) {
                x1 = x2; f1 = f2;
                x2 = xp; f2 = fp;
            } 
            else {
                x3 = xp; f3 = fp;
            }
        }
        // Проверка точности
        if (fabs(x3 - x1) < eps) break;
    }
 */

/*     for (i = 0; i < 1000; i++) {
        // Коэффициенты параболы ax^2 + bx + c
        A = x1 * (f2 - f3) + x2 * (f3 - f1) + x3 * (f1 - f2);
        B = (x1 * x1) * (f2 - f3) + (x2 * x2) * (f3 - f1) + (x3 * x3) * (f1 - f2);
        a = B / (2 * A);
        b = ((x1 * x1 - x2 * x2) * (f2 - f3) + (x2 * x2 - x3 * x3) * (f3 - f1)) / (2 * A);

        // Вершина параболы
        xp = -b / (2 * a);
        fp = f(xp);

        // Обновление точек
        if (xp < x2) {
            if (fp < f2) {
                x3 = x2; f3 = f2;
                x2 = xp; f2 = fp;
            } 
            else {
                x1 = xp; f1 = fp;
            }
        } 
        else {
            if (fp < f2) {
                x1 = x2; f1 = f2;
                x2 = xp; f2 = fp;
            } 
            else {
                x3 = xp; f3 = fp;
            }
        }
        // Проверка точности
        if (fabs(x3 - x1) < eps) break;
    } */
    *iter = i;

    return x2; // Возвращаем точку минимума
}

