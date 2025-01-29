#include <stdio.h>
#include <math.h>

// Функция для поиска последнего числа, равного X, с точностью до epsilon
int find_last_equal(double *sequence, int length, double x, double epsilon) {
    // Находим индекс последнего числа, которое больше X
    int last_index = length - 1;
    
    for (int i = 0; i < length; ++i) {
        if (fabs(sequence[i] - x) <= epsilon) {
            last_index = i;
        }
    }
    
    return last_index;
}

// Пример использования
void main() {
    const int SEQUENCE_SIZE = 8;
    double sequence[] = {1.2, 4.7, 9.8, 10.1, 10.001, 12.3, 13.4, 14.1};
    double x = 10;
    double epsilon = 1e-4;
    int result = find_last_equal(sequence, SEQUENCE_SIZE, x, epsilon);
    
    printf("Последнее число, равное X с точностью до epsilon: %lf\n", sequence[result]);
}