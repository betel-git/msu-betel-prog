#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdio.h>

// создать массив и прочитать его из файла с подсчетом количества чисел 
//
int * ReadArrayCnt(FILE *f, size_t *psize, int *errcode);    

// создать массив и прочитать его из файла, если размер массива задан в файле 
//
int * ReadArrayNum(FILE *f, size_t *psize, int *errcode);    

//  создать массив на заданный размер и заполнить по некоторой формуле
// 
int * GenerateArray(size_t size);

//  напечатать массив с форматированием и комментарием
//
void PrintArray(FILE *f, int *a, size_t size, const char *text);

#endif // ARRAY_H