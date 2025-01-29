#include <stdio.h>
#include <limits.h>

void print_binary(unsigned int n)
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

int main()
{
    unsigned int number = 12345;
    
    printf("Битовое представление числа %u:\n", number);
    print_binary(number);
    
    return 0;
}
