/* Первый код из книги */
#include <stdio.h>
int main(void) {
    int a, b, min;
    // input data
    printf("Введите целое число а ");
    scanf("%d", &a);
    printf("Введите целое b ");
    scanf("%d", &b);
    // computing part
    if (a < b) {
        min = a;
    } else {
        min = b;
    }
    // output result
    printf("Минимум из а = %d и b = %d ", a, b);
    printf("равен %d\n", min);
    return 0;
}