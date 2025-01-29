#include "autotest.h"

int main(void) {
    // инициализация переменных обязательно в самом начале
    FILE *ina, *inb, *output;
    int na = 0, nb = 0;
    double *a, *b;

    // открываем ina.txt
    ina = fopen("ina.txt", "r");
    if(!ina) {
        printf("Error ina.txt\n");
        perror("aaa");
        return -1;
    }

    // открываем inb.txt
    inb = fopen("inb.txt", "r");
    if(!inb) {
        printf("Error inb.txt\n");
        fclose(ina); // закрываем ina
        return -1;
    }

    // открываем output.txt
    output = fopen("output.txt", "w");
    if(!output) {
        printf("Error output.txt\n");
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        return -1;
    }

    // измеряем длину ina
    na = NArray(ina);
    if(na == 0) {
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        return -1;
    }

    // измеряем длину inb
    nb = NArray(inb);
    if(nb == 0) {
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        return -1;
    }

    // читаем a массив
    a = ReadArray(ina, na);
    if(!a) {
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        return -1;
    }
    // закрываем ina, больше не нужен
    fclose(ina);

    // читаем b массив
    b = ReadArray(inb, nb);
    if(!b) {
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        free(a); // освобождаем выделенную под a память
        return -1;
    }
    // закрываем inb, больше не нужен
    fclose(inb);

    // библиотечная сортировка по фукнции сравнения
    qsort(a, na, sizeof(double), cmp);
    qsort(b, nb, sizeof(double), cmp);

    // функциональная часть программы для примера
    for(int i = 0; i < na; i++) {
        fprintf(output, "%f\n", a[i]);
    }
    for(int j = 0; j < nb; j++) {
        fprintf(output, "%f\n", a[j]);
    }

    // закрываем все файлы, освобождаем память
    fclose(output);
    free(a);
    free(b);


    return 0;
}