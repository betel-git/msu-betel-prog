//
// прототипы функций для работы с массивами
// 
#ifndef ARRAY_H      // для единственности включения
#define ARRAY_H

// прототипы библиотечных функций
#include <stddef.h>   // это для size_t
#include <stdio.h>


// создать массив и прочитать его из файла с подсчетом количества чисел 
//
double * ReadArrayCnt(FILE *f, size_t *psize, int *errcode);    

// создать массив и прочитать его из файла, если размер массива задан в файле 
//
double * ReadArrayNum(FILE *f, size_t *psize, int *errcode);    

//  создать массив на заданный размер и заполнить по некоторой формуле
// 
double * GenerateArray(size_t size);

//  напечатать массив с форматированием и комментарием
//
void PrintArray(FILE *f, double *a, size_t size, const char *text);

#endif // ARRAY_H