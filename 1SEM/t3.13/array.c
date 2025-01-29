#include "3.13.h"
// позаимствовано :)
unsigned int * ReadArrayCnt(FILE *f, long long int *size, int *errcode) {
    long long int i;    // счетчик
    unsigned int x;    // для ввода очередного числа
    unsigned int *a;   // указатель на массив

    *errcode = 0;  // надеемся, что все будет хорошо

    // а вдруг файл не открыт!
    if (!f) {
       *size = 0;
       *errcode = -1; // file is not opened 
       return 0;
    }

    // подсчет количества чисел
    for (i=0; fscanf(f,"%u",&x)==1; i++);
    //printf("%ld\n", i);
    *size = i;
    if (*size == 0) { // в файле нет чисел
       *errcode = -2; // no numbers in file 
       return 0;
    }
    //printf("111%ln\n", size);
    // создание массива
    a = (unsigned int*)malloc(*size*sizeof(unsigned int));
    if (!a) {
       *errcode = -3; // memory allocation error 
        return 0;
    }

    // возврат в начало и чтение массива

    rewind(f);
  
    for (i=0; i<*size && fscanf(f,"%u", &a[i])==1; i++);
    if (i != *size) { // а вдруг все испортилось!
       *errcode = -4; // rereading error 
       free(a);
       return 0;
    } 

    rewind(f);

    return a;
}