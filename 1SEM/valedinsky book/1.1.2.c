#include <stdio.h>
int Min(int, int);
int main(void) {
    int a, b, abMin;
    printf("Введите целые а и б \t");
    scanf("%d%d", &a, &b);
    abMin = Min(a, b);
    printf("min(%d, %d) = %d \n", a, b, abMin);
    return 0;
}
int Min(int x, int y) {
    int z;
    z = (x < y) ? x : y;
    return z;
}