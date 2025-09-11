#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Area(int *x, int *y, int n);
double ModArea(int *x, int *y, int n, double a, double b);

// функция берёт первую точку и относительно неё
// триангулирует многоугольник и считает его площадь
double Area(int *x, int *y, int n) {
    double res = 0;
    int vx, vy, ux = 0, uy = 0, i;
    for (i = 0; i < n; i++) {
        vx = ux;
        vy = uy;
        ux = x[i + 1] - x[0];
        uy = y[i + 1] - y[0];
        res += (vx * uy - ux * vy) / 2.0;
    }
    return fabs(res);
}

// всё, что и Area
// + добавляет площадь треугольника приращения
double ModArea(int *x, int *y, int n, double a, double b) {
    double res = 0;
    double vx, vy, ux = 0, uy = 0;
    int i;
    for (i = 0; i < n; i++) {
        vx = ux;
        vy = uy;
        ux = x[i + 1] - x[0];
        uy = y[i + 1] - y[0];
        res += (vx * uy - ux * vy) / 2.0;
    }
    vx = ux;
    vy = uy;
    ux = a - x[0];
    uy = b - y[0];
    res += (vx * uy - ux * vy) / 2.0;
    return fabs(res);
}


int main(void) {
    int n, mid, i, left, right;
    int* x;
    int* y;
    FILE* in;
    double init_area, target, new_area, eps = 1e-8, a, b, x1, x2, y1, y2;
    
    in = fopen("input.txt", "r");
    if (!in) {
        printf("Error input.txt\n");
        return -1;
    }

    if (fscanf(in, "%d", &n) != 1) {
        printf("fscanf error 1\n");
        fclose(in);
        return -1;
    }

    if (n ==  1 || n == 2) {
        printf("Площадь равна нулю.\n");
        return 0;
    }

    x = (int *)malloc(n * sizeof(int));
    if (!x) {
        printf("Malloc error 1\n");
        x = 0;
        fclose(in);
        return -1;
    }
    y = (int *)malloc(n * sizeof(int));
    if (!y) {
        printf("Malloc error 2\n");
        free(x);
        fclose(in);
        y = 0;
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (fscanf(in, "%d %d", &x[i], &y[i]) != 2) {
            printf("fscanf error 2\n");
            free(x); free(y); fclose(in);
            return -1;
        }
    }

    init_area = Area(x, y, n);
    target = init_area / 2.0;
    left = 0;
    right = n;
    // найдём две соседние точки, между которыми должна
    // находиться третья, искомая, точка
    while (right - left > 1) {
        mid = (right + left) / 2;
        //printf("%d - mid\n", mid);
        new_area = Area(x, y, mid);
        if (fabs(target - new_area) < eps) break;
        if (target >= new_area) left = mid;
        else right = mid;
        //printf("%d %d %d - lmr\n", left, mid, right);
    }
    if ((new_area > target)) mid -= 1;

    if (fabs(target - new_area) < eps) {
        // если сразу попали в ответ
        printf("Прямую можно построить по двум точкам: (%d, %d) и (%d, %d)\n", x[mid], y[mid], x[0], y[0]);
        printf("(x - %d) / (%d - %d) = (y - %d) / (%d - %d)\n", x[0], x[mid], x[0], y[0], y[mid], y[0]);
        printf("(area, target) = (%lg, %lg)\n", new_area, target);
        printf("Площадь изначальной фигуры равна: %lg\n", init_area);
        fclose(in); free(x); free(y);
        return 0;
    }
    else {
        // биссекцией ищем нужную точку
        //printf("%lg %lg %d\n", a, b, mid);
        x2 = x[mid + 1];
        x1 = x[mid];
        y2 = y[mid + 1];
        y1 = y[mid];
        while (fabs(new_area - target) >= eps) {
            a = (x2 + x1) / 2.0;
            b = (y2 + y1) / 2.0;
            new_area = ModArea(x, y, mid, a, b);
            //printf("%lg - new area\n", new_area); 
            if (new_area <= target) {
                x1 = a;
                y1 = b;
            }
            else {
                x2 = a;
                y2 = b;
            }
        }
    }
    //printf("\n");
    printf("Прямую можно построить по двум точкам: (%lg, %lg) и (%d, %d)\n", a, b, x[0], y[0]);
    printf("Уравнение прямой: (x - %d) / (%lf - %d) = (y - %d) / (%lf - %d)\n", x[0], a, x[0], y[0], b, y[0]);
    printf("(area, target) = (%lg, %lg)\n", new_area, target);
    printf("Площадь изначальной фигуры равна: %lg\n", init_area);
    fclose(in); free(x); free(y);
    return 0;
}