#include "lastnumber.h"
void TestCalculation (const char * filenamei, const char * filenameo);

void TestCalculation (const char * filenamei, const char * filenameo) {
    // точность сравнения чисел, заданное число, результат (индекс)
    double epsilon, x, res;
    FILE * f;
    FILE * fo;

    // открытие файла и его проверка на пустоту
    f = fopen(filenamei, "r");
    if (!f) {
        fprintf(stderr, "Error opening data file\n");
    }

    // задаём epsilon
    printf("epsilon: ");
    scanf("%le", &epsilon); // epsilon = float(input())
    printf("x: ");
    scanf("%le", &x);

    // получение результата и его обработка
    res = Lastnumber(f, epsilon, x);
    fo = fopen(filenameo, "w");
    if (fabs(res + 1) <= epsilon) {
        fprintf(fo, "There is no such number\n");
    }
    else {
        fprintf(fo, "Last number`s index is %f\n", res);
    }

    // освобождение ресурсов
    fclose(f);
    fclose(fo);
}

// непосредственно тестирование
int main(void) {
    TestCalculation("input1.txt", "output1.txt");
    TestCalculation("input2.txt", "output2.txt");
    return 0;
}