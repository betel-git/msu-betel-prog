#include <stdio.h>
#include <stdlib.h>

void count_bits(unsigned int n, int *ones, int *zeros);
void onebits(int a, int b, char *filename);

// Функция для подсчета количества единиц и нулей в двоичном представлении числа
/* void count_bits(unsigned int n, int *ones, int *zeros) {
    int count = 0;
    *ones = 0;
    *zeros = 0;
    //printf("%d\n", n);
    if((n & 1) == 0) (*zeros)++;
    // Пропускаем ведущие нули до первой единицы
    //n >>= 1;
    while ((n & 1) == 0 && (n > 0)) {
        n >>= 1;
        count++;
        printf("count %d\n", count);
    }
        
    // Подсчитываем количество единиц и нулей после старшей единицы
    while (count < 32) {
        if (n & 1) {
            (*ones)++;
        }
        if ((n & 1) == 0) {
            (*zeros)++;
        }
        n >>= 1;
        count++;
    }
    
    
    //printf("one %d\n", ones);
    //printf("zero %d\n", zeros);
    //printf("\n");
} */

// Функция для подсчёта количества единиц и нулей в двоичном представлении числа
void count_bits(unsigned int n, int *ones, int *zeros) {
    *ones = 0;
    *zeros = 0;

    // Если число равно нулю, то оно состоит из одного нуля
    if (n == 0) {
        (*zeros)++;
        return;
    }

    // Перебираем все биты числа от младшего к старшему
    while (n != 0) {
        if (n & 1) {   // Проверяем младший бит
            (*ones)++; // Если он равен 1, увеличиваем счётчик единиц
        } else {
            (*zeros)++; // Иначе увеличиваем счётчик нулей
        }
        n >>= 1;       // Сдвигаем число вправо на один бит
    }
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
        printf("i %d\n", i);
        count_bits(i, &ones, &zeros);
        printf("%d\n", ones);
        printf("%d\n", zeros);
        printf("\n");
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