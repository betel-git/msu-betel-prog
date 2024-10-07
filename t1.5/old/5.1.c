#include "5.1prog.h"

// Пример использования
int main(void) {
    const int SEQUENCE_SIZE = 11;
    double sequence[] = {1.2, 4.7, 9.8, 10.1, 10.001, 12.3, 13.4, 14.1, 6.8, 5.7, 11};
    double x = 10;
    double epsilon = 1e-4;
    int result = find_last_equal(sequence, SEQUENCE_SIZE, x, epsilon);
    
    printf("The last number equal to X with an accuracy to Epsilon:: %lf\n", sequence[result]);
    return 0;
}
