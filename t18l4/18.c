#include "sumnumbers.h"

void TestCalculation (const char * fni, const char * fno);
// fni == filenameinput, fno == filenameoutput
void TestCalculation (const char * fni, const char * fno) {
    int res; // переменная для записи результата
    FILE * f; // f == file input
    FILE * fo; // fo == file output

    // открываем входной файл и проверяем его
    f = fopen(fni, "r");
    if (!f) {
        fprintf(stderr, "Error opening data file\n");
    }

    // получаем результат и записываем его в выходной файл
    res = SumNumbers(f);
    fo = fopen(fno, "w");
    fprintf(fo, "%i", res);

    // освобождаем ресурсы
    fclose(f);
    fclose(fo);
}

int main(void) {
    // тесты на двух разных файлах
    TestCalculation("input1.txt", "output1.txt");
    TestCalculation("input2.txt", "output2.txt");
    return 0;
}