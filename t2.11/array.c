#include <stdlib.h>
#include "array.h"

double * ReadArrayCnt(FILE *f, size_t *size, int *errcode) {
    size_t i;    // счетчик
    double x;    // для ввода очередного числа
    double *a;   // указатель на массив

    *errcode = 0;  // надеемся, что все будет зорошо

    // а вдруг файл не открыт!
    if (!f) {
       *size = 0;
       *errcode = -1; // file is not opened 
       return 0;
    }

    // подсчет количества чисел
    for (i=0; fscanf(f,"%lf",&x)==1; i++);
    *size = i;
    if (*size == 0) { // в файле нет чисел
       *errcode = -2; // no numbers in file 
       return 0;
    }

    // создание массива
    a = (double*)malloc(*size*sizeof(double));
    if (!a) {
       *errcode = -3; // memory allocation error 
        return 0;
    }

    // возврат в начало и чтение массива

    rewind(f);
  
    for (i=0; i<*size && fscanf(f,"%lf", &a[i])==1; i++);
    if (i != *size) { // а вдруг все испортилось!
       *errcode = -4; // rereading error 
       free(a);
       return 0;
    } 

    return a;
}