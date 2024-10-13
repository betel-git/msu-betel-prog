#include <stdlib.h>
#include "array.h"

// создать массив и прочитать его из файла с подсчетом количества чисел 
//
int * ReadArrayCnt(FILE *f, size_t *size, int *errcode)
{
    size_t i;    // счетчик
    int x;    // для ввода очередного числа
    int *a;   // указатель на массив

    *errcode = 0;  // надеемся, что все будет зорошо

    // а вдруг файл не открыт!
    if (!f) {
       *size = 0;
       *errcode = -1; // file is not opened 
       return 0;
    }

    // подсчет количества чисел
    for (i=0; fscanf(f,"%d",&x)==1; i++);
    *size = i;
    if (*size == 0) { // в файле нет чисел
       *errcode = -2; // no numbers in file 
       return 0;
    }

    // создание массива
    a = (int*)malloc(*size*sizeof(int));
    if (!a) {
       *errcode = -3; // memory allocation error 
        return 0;
    }

    // возврат в начало и чтение массива

    rewind(f);
  
    for (i=0; i<*size && fscanf(f,"%i", &a[i])==1; i++);
    if (i != *size) { // а вдруг все испортилось!
       *errcode = -4; // rereading error 
       free(a);
       return 0;
    } 

    return a;
}


// создать массив и прочитать его из файла, если размер массива задан в файле 
//
int * ReadArrayNum(FILE *f, size_t *size, int *errcode)    
{
    size_t i;    // счетчик
    int *a;   // указатель на массив

    *errcode = 0;  // надеемся, что все будет зорошо

    // а вдруг файл не открыт!
    if (!f) {
       *size = 0;
       *errcode = -1; // file is not opened 
       return 0;
    }

    // читаем количество чисел
    //if ( fscanf(f,"%llu", size) != 1) {  // в разных компиляторах могут быть разные  
    if ( fscanf(f,"%zu", size) != 1) {      // спецификации ввода size_t --- %zu или %llu
       *size = 0;
       *errcode = -2;  // cannot read array length  
       return 0;
    }

    // создание массива
    a = (int*)malloc(*size*sizeof(int));
    if (!a) {
       *errcode = -3; // memory allocation error 
        return 0;
    }

    // чтение массива
    for (i=0; i<*size && fscanf(f,"%i", &a[i])==1; i++);

    *size = i;  // сколько фактически прочитали

    return a;
}

//  создать массив на заданный размер и заполнить по некоторой формуле
// 
int * GenerateArray(size_t size)
{
    size_t i;
    int *a;
    a = (int*)malloc(size*sizeof(int));
    if (!a) {
        return 0;
    }
    for (i = 0; i < size; i++) {
        a[i] = (int)(rand()%1000); // случайные от 0 до 999
    }
    return a;
}

//  напечатать массив с форматированием и комментарием
//
void PrintArray(FILE *f, int *a, size_t size, const char *text)
{
    size_t i; 
    int rowN = 5;
    if (text) { fprintf(f, "%s", text); } 
    for (i = 0; i < size; i++) {
        fprintf(f,"%s%d", (i%rowN == 0) ? "\n":"  ", a[i]);
    }
    fprintf(f, "\n");
}