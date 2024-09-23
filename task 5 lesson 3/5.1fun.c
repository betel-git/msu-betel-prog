#include "5.1prog.h"

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