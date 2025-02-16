#include "t1ex1.h"

int main() {
    long long n, n_for_factorial;
    double res1, res2, res3, res4, res5, res6, res7, res8, res9, res10;
    printf("n = ");
    scanf("%lld", &n);
    printf("n_for_factorial = ");
    scanf("%lld", &n_for_factorial);
    res1 = Func1(n);
    res2 = Func1rev(n);
    printf("res1: %lf\n", res1);
    printf("res2: %lf\n", res2);

    res3 = Func2(n);
    res4 = Func2rev(n);
    printf("res3: %lf\n", res3);
    printf("res4: %lf\n", res4);

    res5 = Func3(n);
    res6 = Func3rev(n);
    printf("res5: %lf\n", res5);
    printf("res6: %lf\n", res6);

    res7 = Func4(n);
    res8 = Func4rev(n);
    printf("res7: %lf\n", res7);
    printf("res8: %lf\n", res8);

    res9 = Func5(n_for_factorial);
    res10 = Func5rev(n_for_factorial);
    printf("res9: %lf\n", res9);
    printf("res10: %lf\n", res10);
    return 0;
}