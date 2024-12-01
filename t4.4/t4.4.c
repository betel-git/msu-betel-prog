#include "t4.4.h"
#include <stdio.h>
#include <stdint.h>

void print_binary(int n)
{
    // Максимальное количество битов в unsigned int
    const int num_bits = sizeof(n) * CHAR_BIT;
    
    for (int i = num_bits - 1; i >= 0; i--)
    {
        printf("%d", (n >> i) & 1);
        
        if (i % 8 == 0 && i != 0)
            printf(" ");
    }
}

int main(void)
{
    int rnum;
    int num;
    // Вводим число
    printf("Введите число: ");
    scanf("%d", &num);

    printf("\nБитовое представление исходного числа:\n");
    print_binary(num);

    // Перестановка байтов
    rnum = ((num >> 24) & 0xFF) |
                    ((num << 8) & 0x00FF0000) |
                    ((num >> 8) & 0x0000FF00) |
                    ((num << 24) & 0xFF000000);

    // Печатаем результат
    printf("\nПолученное число после перестановки байт: %d\n", rnum);

    // Печатаем байты полученного числа
    printf("\nБитовое представление нового числа:\n");
    print_binary(rnum);

    return 0;
}
