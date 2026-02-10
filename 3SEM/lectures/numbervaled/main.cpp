#include <stdio.h>
#include <math.h>

#include "Number.h"
/*
   Несколько тестов для вычисления с контролем погрешности операций.
   Сначала проверка простейших операций.
   Потом сравниваются вычисления интеграла по простейшей формуле прямоугольников.
   Далее суммирование последовательности в прямом и обратном направлениях.
   В конце просто суммирование единицы много-много раз.
*/

double  SimpleIntegration(double(*f) (double), double a, double b, int n);
NumberA  SimpleIntegrationA(NumberA(*f) (NumberA), NumberA a, NumberA b, int n);
NumberA  sinA(NumberA x);

// примитивный метод прямоугольников
double  SimpleIntegration(double(*f) (double), double a, double b, int n)
{
    int i;
    double h, s;
    h = (b - a) / n;
    s = 0;
    for (i = 0; i < n; i++) {
        s += f(a + i*h)*h;
    }
    return s;
}

NumberA  SimpleIntegrationA (NumberA(*f) (NumberA), NumberA a, NumberA b, int n)
{
    int i;
    NumberA h, s;
    h = (b - a) / n;
    s = 0;
    for (i = 0; i < n; i++) {
        s += f(a + i*h)*h;
    }
    return s;
}

// переопределение функции sin
NumberA sinA(NumberA x)
{
    // для простоты считаем, что погрешность просто сохраняется (|sin'x|<=1)
    x.value = sin(x.value);
    return x;
}

int main()
{
    int k, n;
    double s1;
    double PI = 3.14159265358979323L;
    NumberA NPI (PI);
    NumberA s2;

    NumberA x = 123;
    NumberA y = 456;
    NumberA z;

    // примитивные операции
    printf("x=%.20f  err=%.6e\n", x.Value(), x.Error());
    printf("y=%.20f  err=%.6e\n", y.Value(), y.Error());
    z = x + y;
    printf("z=x+y=%.20f  err=%.6e\n", z.Value(), z.Error());
    z = x - y;
    printf("z=x-y=%.20f  err=%.6e\n", z.Value(), z.Error());
    z = x * y;
    printf("z=x*y=%.20f  err=%.6e\n", z.Value(), z.Error());
    z = x / y;
    printf("z=x/y=%.20f  err=%.6e\n", z.Value(), z.Error());
    z = y / x;
    printf("z=y/x=%.20f  err=%.6e\n", z.Value(), z.Error());
    y = ++z;
    printf("y = ++z   y %.20f  err=%.6e   z %.20f  err=%.6e\n", y.Value(), y.Error(), z.Value(), z.Error());
    y = z++;
    printf("y = z++   y %.20f  err=%.6e   z %.20f  err=%.6e\n", y.Value(), y.Error(), z.Value(), z.Error());

    
    // ставнение двух функций интегрирования
    printf("integration with double\n");
    n = 10;
    for (k = 1; k <= 5; k++) {
        n *=10;
        s1 = SimpleIntegration(sin, 0, 2*PI, n);
        printf("n=%9d  s1=%e\n", n, s1);
    }

    printf("integration with NumberA\n");
    n = 10;
    for (k = 1; k <= 5; k++) {
        n *= 10;
        s2 = SimpleIntegrationA(sinA, 0, 2*NPI, n);
        printf("n=%9d  s1=%e  err=%.6e\n", n, s2.Value(), s2.Error());
    }
    printf("interval %.20f  %.20f\n", s2.Value() - s2.Error(),  s2.Value() + s2.Error());


    printf("direct sum\n");
    n = 10000000; 
    s2 = 0;
    for (k=1; k<=n; k++) {
        s2 += k*NPI;
//        if (k%1000000==0)     printf("n=%d  s2=%.20f  err=%.6e\n", k, s2.Value(), s2.Error());

    }
    printf("n=%d  s2=%.20f  err=%.6e\n", n, s2.Value(), s2.Error());
    printf("interval %.20f  %.20f\n", s2.Value() - s2.Error(),  s2.Value() + s2.Error());

    printf("reverse sum\n");
    n = 10000000; 
    s2 = 0;
    for (k=n; k>0; k--) {
        s2 += k*NPI;
//        if (k%1000000==0)     printf("n=%d  s2=%.20f  err=%.6e\n", k, s2.Value(), s2.Error());
    }
    printf("n=%d  s2=%.20f  err=%.6e\n", n, s2.Value(), s2.Error());
    printf("interval %.20f  %.20f\n", s2.Value() - s2.Error(),  s2.Value() + s2.Error());

    n = 1000000000; 
    s2 = 0;
    printf("sum test\n");
    for (k=0; k<n; k++) {
        s2 += 1;
    }
    printf("n=%d  s2=%.20f  err=%.6e\n", n, s2.Value(), s2.Error());
    return 0;
}
