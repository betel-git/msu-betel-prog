#include "headers.h"


double ParabolicGeometry(double (*f)(double), double x1, double x3, double eps, int *iter, double *err) {
    double x2 = (x1 + x3) / 2;
    double f1 = f(x1), f2 = f(x2), f3 = f(x3);
    double alpha = 0.5;
    double a, b, c;
    double xp, fp;
    int i;
    int help = 0;
    double x1help, x3help;
    *iter = 0, *err = 0;
    
    for (i = 0; i < 100; i++) {
        //printf("%d %lf %lf %lf %lf\n", i, x1, x2, x3, xp);
        if (fabs(x3 * (x3 - x1 - x2) + x1 * x2) < 1e-15 || fabs(x2 - x1) < 1e-15) break;
        a = (f3 - (x3 * (f2 - f1) + x2 * f1 - x1 * f2) / (x2 - x1)) / (x3 * (x3 - x1 - x2) + x1 * x2);
        b = ((f2 - f1) / (x2 - x1)) - a * (x1 + x2);
        c = ((x2 * f1 - x1 * f2) / (x2 - x1)) + a * x1 * x2;
    
        // Вершина параболы
        if (fabs(a) < 1e-15) break;
        xp = -b / (2 * a);
        //printf("xp: %.15le\n", xp);
        fp = a * xp * xp + b * xp + c;

        // Обновление трёх точек
        if (xp > x2) {
            if (fp < f2) {
                x1 = x2; f1 = f2;
                x2 = xp; f2 = f(xp);
                //printf("check 1\n");
            } else {
                x3 = xp; f3 = f(xp);
                //printf("check 2\n");
            }
        } else {
            if (fp < f2) {
                x3 = x2; f3 = f2;
                x2 = xp; f2 = f(xp);
                //printf("check 3\n");
            } else {
                x1 = xp; f1 = f(xp);
                //printf("check 4\n");
            }
        }
        
        // Измельчение интервала с помощью геометрической прогрессии
        if (fabs(x3 - x1) > eps) {
            alpha = 0.5;
            x1 = x2 - (alpha * (x2 - x1));
            x3 = x2 + (alpha * (x3 - x2));
            f1 = f(x1);
            f3 = f(x3);
            //printf("check 5\n");
        }
        else break;

        // Поиск плато
        if (f3 >= f1 && f1 >= f3) {
            help++;
            if (help == 1) {
                x1help = x1;
                x3help = x3;
                printf("MAY BE PLATEAU\n");
            }
            else if (help == 2) {
                printf("DEFINITELY PLATEAU\n");
                *err = fabs(x3help - x1help);
                return (x3help + x1help) / 2; 
            }
        }
        else help = 0;
    }
    *iter = i;
    return x2;
}


double ParabolicGrid(double (*f)(double), double x1, double x3, double eps, int *iter, double *err) {
    double x2 = (x1 + x3) / 2;
    double f1 = f(x1), f2 = f(x2), f3 = f(x3);
    double a, b, c;
    double xp, fp;
    int i;
    double step, min_f, min_x, xi, fi, new_range, grid_points = 5;
    int help = 0;
    double x1help, x3help;
    *iter = 0, *err = 0;
    
    for (i = 0; i < 100; i++) {
        //printf("%d %lf %lf %lf %lf\n", i, x1, x2, x3, xp);
        if (fabs(x3 * (x3 - x1 - x2) + x1 * x2) < 1e-15 || fabs(x2 - x1) < 1e-15) break;
        a = (f3 - (x3 * (f2 - f1) + x2 * f1 - x1 * f2) / (x2 - x1)) / (x3 * (x3 - x1 - x2) + x1 * x2);
        b = ((f2 - f1) / (x2 - x1)) - a * (x1 + x2);
        c = ((x2 * f1 - x1 * f2) / (x2 - x1)) + a * x1 * x2;
    
        // Вершина параболы
        if (fabs(a) < 1e-15) break;
        xp = -b / (2 * a);
        //printf("xp: %.15le\n", xp);
        fp = a * xp * xp + b * xp + c;

        // Обновление трёх точек
        if (xp > x2) {
            if (fp < f2) {
                x1 = x2; f1 = f2;
                x2 = xp; f2 = f(xp);
                //printf("check 1\n");
            } else {
                x3 = xp; f3 = f(xp);
                //printf("check 2\n");
            }
        } else {
            if (fp < f2) {
                x3 = x2; f3 = f2;
                x2 = xp; f2 = f(xp);
                //printf("check 3\n");
            } else {
                x1 = xp; f1 = f(xp);
                //printf("check 4\n");
            }
        }
        
        // Измельчение интервала с помощью измельчения сетки
        if (fabs(x3 - x1) > eps) {
            step = (x3 - x1)/grid_points; // Шаг сетки
            min_f = f2;
            min_x = x2;
            
            // Поиск точки с минимальным значением на сетке
            for (i = 1; i < grid_points; i++) {
                xi = x1 + i*step;
                fi = f(xi);
                if (fi < min_f) {
                    min_f = fi;
                    min_x = xi;
                }
            }
            
            // Обновление интервала вокруг новой точки
            new_range = (x3 - x1)/2.0;
            x1 = min_x - new_range/2.0;
            x3 = min_x + new_range/2.0;
            f1 = f(x1);
            f3 = f(x3);
            x2 = min_x;
            f2 = min_f;
        }
        else break;

        // Поиск плато
        if (f3 >= f1 && f1 >= f3) {
            help++;
            if (help == 1) {
                x1help = x1;
                x3help = x3;
                printf("MAY BE PLATEAU\n");
            }
            else if (help == 2) {
                printf("DEFINITELY PLATEAU\n");
                *err = fabs(x3help - x1help);
                return (x3help + x1help) / 2; 
            }
        }
        else help = 0;
    }
    *iter = i;
    return x2;
}


double ParabolicGolden(double (*f)(double), double x1, double x3, double eps, int *iter, double *err) {
    double x2 = (x1 + x3) / 2;
    double f1 = f(x1), f2 = f(x2), f3 = f(x3);
    double a, b, c;
    double xp, fp;
    int i;
    double x_left, x_right, f_left, f_right;
    double GoldenRatio = (sqrt(5) - 1) / 2;
    int help = 0;
    double x1help, x3help;
    *iter = 0, *err = 0;
    
    for (i = 0; i < 100; i++) {
        //printf("%d %lf %lf %lf %lf\n", i, x1, x2, x3, xp);
        if (fabs(x3 * (x3 - x1 - x2) + x1 * x2) < 1e-15 || fabs(x2 - x1) < 1e-15) break;
        a = (f3 - (x3 * (f2 - f1) + x2 * f1 - x1 * f2) / (x2 - x1)) / (x3 * (x3 - x1 - x2) + x1 * x2);
        b = ((f2 - f1) / (x2 - x1)) - a * (x1 + x2);
        c = ((x2 * f1 - x1 * f2) / (x2 - x1)) + a * x1 * x2;
    
        // Вершина параболы
        if (fabs(a) < 1e-15) break;
        xp = -b / (2 * a);
        //printf("xp: %.15le\n", xp);
        fp = a * xp * xp + b * xp + c;

        // Обновление трёх точек
        if (xp > x2) {
            if (fp < f2) {
                x1 = x2; f1 = f2;
                x2 = xp; f2 = f(xp);
                //printf("check 1\n");
            } else {
                x3 = xp; f3 = f(xp);
                //printf("check 2\n");
            }
        } else {
            if (fp < f2) {
                x3 = x2; f3 = f2;
                x2 = xp; f2 = f(xp);
                //printf("check 3\n");
            } else {
                x1 = xp; f1 = f(xp);
                //printf("check 4\n");
            }
        }
        
        if (fabs(x3 - x1) > eps) {
            x_left = x3 - GoldenRatio * (x3 - x1);
            x_right = x1 + GoldenRatio * (x3 - x1);
            f_left = f(x_left);
            f_right = f(x_right);
            
            if (f_left < f_right) {
                x3 = x_right;
                f3 = f_right;
                x2 = x_left; 
                f2 = f_left;
            } else {
                x1 = x_left;
                f1 = f_left;
                x2 = x_right;
                f2 = f_right;
            }
        }
        else break;

        // Поиск плато
        if (f3 >= f1 && f1 >= f3) {
            help++;
            if (help == 1) {
                x1help = x1;
                x3help = x3;
                printf("MAY BE PLATEAU\n");
            }
            else if (help == 2) {
                printf("DENIFITELY PLATEAU\n");
                *err = fabs(x3help - x1help);
                return (x3help + x1help) / 2; 
            }
        }
        else help = 0;
    }
    *iter = i;
    return x2;
}