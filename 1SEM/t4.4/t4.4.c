#include "t4.4.h"
#include <stdio.h>
#include <stdint.h>

void PrintBinary(int n) {
    // максимальное количество битов в unsigned int
    const int num_bits = sizeof(n) * CHAR_BIT;
    for (int i = num_bits - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0)
            printf(" ");
    }
}

int main(void)
{
    int rnum;
    int num;
    printf("Введите число: ");
    scanf("%d", &num);

    printf("\nБитовое представление исходного числа:\n");
    PrintBinary(num);

    // перестановка байтов
    rnum = ((num >> 24) & 0xFF) |
           ((num << 8) & 0x00FF0000) |
           ((num >> 8) & 0x0000FF00) |
           ((num << 24) & 0xFF000000);

    printf("\nПолученное число после перестановки байт: %d\n", rnum);
    printf("\nБитовое представление нового числа:\n");
    PrintBinary(rnum);

    return 0;
}
