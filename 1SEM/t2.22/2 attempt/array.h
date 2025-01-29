//
// прототипы функций для работы с массивами
// 
#ifndef ARRAY_H      // для единственности включения
#define ARRAY_H

// прототипы библиотечных функций
#include <stddef.h>
#include <stdio.h>


// создать массив и прочитать его из файла с подсчетом количества чисел 
//
int * ReadArrayCnt(FILE *f, size_t *psize, int *errcode);    

#endif // ARRAY_H
