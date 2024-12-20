#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void count_bits(int n, int ones, int zeros);
void onebits(int a, int b, char *filename);


/* void PrintBinary(int n) {
    // максимальное количество битов в unsigned int
    const int num_bits = sizeof(n) * 8;
    for (int i = num_bits - 1; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 8 == 0 && i != 0)
            printf(" ");
    }
}
 */
// Функция для подсчета количества единиц и нулей в двоичном представлении числа
void count_bits(int n, int ones, int zeros) {
    //ones = 0;
   // zeros = 0;
    
    // Пропускаем ведущие нули до первой единицы
    n >>= 1;
    while ((n & 1) == 0 && n > 0)
        n >>= 1;
        
    // Подсчитываем количество единиц и нулей после старшей единицы
    while (n > 0) {
        if (n & 1) {
            ones++;
        }
        else {
            zeros++;
        }
        n >>= 1;
    }
    printf("\n");
    printf("one %d\n", ones);
    printf("zero %d\n", zeros);
}

// Основная функция для поиска чисел с равным количеством единиц и нулей
void onebits(int a, int b, char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка при открытии файла");
        return;
    }

    for (int i = a; i <= b; ++i) {
        int ones = 0, zeros = 0;
        count_bits(i, ones, zeros);
        
        if (ones == zeros) {
            fprintf(file, "%d\n", i);
        }
    }

    fclose(file);
}

// Пример использования функции
int main(void) {
    char filename[256];
    int a, b;
    printf("Введите имя выходного файла: ");
    scanf("%s", filename);
    printf("Введите а: ");
    scanf("%d", &a);
    printf("Введите b: ");
    scanf("%d", &b);
    onebits(a, b, filename);
    printf("Запись завершена. Результаты сохранены в %s.\n", filename);
    return 0;
}