#include "04_11.h"

int main(void){
    int x, y;
    printf("Input x, y : ");
    scanf("%d %d", &x, &y);
    printf("x : %d  Ans : %x  Re : %d\n", x, DecToDec4(x), Dec4ToDec(DecToDec4(x)));
    printf("y : %d  Ans : %x  Re : %d\n", y, DecToDec4(y), Dec4ToDec(DecToDec4(y)));
    printf("Sum x + y : %x  Re : %d\n", Sum(x, y), Dec4ToDec(Sum(x, y)));
    return 0;
}
