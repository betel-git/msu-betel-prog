#include <stdio.h>
#include <stdlib.h>
int f(int n, int m);
int f(int n, int m) {
    if (n == 0 || m == 0) return 1;
    return (f(n - 1, m) + f(n, m - 1));
}
int main(void) {
    printf("%d\n", f(4,3));
    return 0;
}