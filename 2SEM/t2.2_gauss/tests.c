#include "headers.h"

// умножение всех элементов на константу
void ConstMultiplication (double **a, int rows, int cols, double c) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            a[i][j] *= c;
        }
    }
}