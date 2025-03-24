#include "headers.h"

int main(void) {
    double x1 = -10.0, x3 = 13.0;
    double eps = 1e-10;
    int iter = 0;
    double err = 0;
    double x_min, f_min;
    double(*f[])(double) = {f1, f2, f3};
    int i;

    printf("Parabolic search + Geometric progression:\n");
    for (i = 0; i < 3; i++) {
        x_min = ParabolicGeometry(*f[i], x1, x3, eps, &iter, &err);
        f_min = f[i](x_min);
        if (iter >= 100) printf("%d) error\n", i);
        else printf("%d) success\n", i);
        printf("iter = %d\n", iter);
        printf("x = %.15le, f(x) = %.15le\n", x_min, f_min);
        printf("err = %le\n", err);
        printf("-----------------\n");
    }

    printf("\n\nParabolic search + Grid division:\n");
    for (i = 0; i < 3; i++) {
        x_min = ParabolicGrid(*f[i], x1, x3, eps, &iter, &err);
        f_min = f[i](x_min);
        if (iter >= 100) printf("%d) error\n", i);
        else printf("%d) success\n", i);
        printf("iter = %d\n", iter);
        printf("x = %.15le, f(x) = %.15le\n", x_min, f_min);
        printf("err = %le\n", err);
        printf("-----------------\n");
    }

    printf("\n\nParabolic search + Golden ratio:\n");
    for (i = 0; i < 3; i++) {
        x_min = ParabolicGolden(*f[i], x1, x3, eps, &iter, &err);
        f_min = f[i](x_min);
        if (iter >= 100) printf("%d) error\n", i);
        else printf("%d) success\n", i);
        printf("iter = %d\n", iter);
        printf("x = %.15le, f(x) = %.15le\n", x_min, f_min);
        printf("err = %le\n", err);
        printf("-----------------\n");
    }

/*     printf("Parabolic Search:\n");
    for (i = 0; i < 4; i++) {
        x_min = ParabolicSearch(*f[i], x1, x3, eps, &iter);
        f_min = f[i](x_min);
        if (iter >= 100) printf("%d) error\n", i);
        else printf("%d) success\n", i);
        printf("iter = %d\n", iter);
        printf("x = %.15le, f(x) = %.15le\n", x_min, f_min);
        printf("-----------------\n");
    } */

/*     printf("\nGolden Search:\n");
    for (i = 0; i < 4; i++) {
        x_min = GoldenSearch(*f[i], x1, x3, eps, &iter, &err);
        f_min = f[i](x_min);
        if (iter >= 1000) printf("%d) error\n", i);
        else printf("%d) success\n", i);
        printf("err = %le\n", err);
        printf("iter = %d\n", iter);
        printf("x = %.15le, f(x) = %.15le\n", x_min, f_min);
        printf("-----------------\n");
    } */

    return 0;
}