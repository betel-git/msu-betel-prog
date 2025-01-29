// 
//  пример простейшего кода для обработки массива
// 

// прототипы библиотечных функций
#include <stdio.h>
#include <stdlib.h>

// прототипы наших функций
#include "minmax2.h"
#include "array.h"

// тест обработки массива

int main(void)
{
   FILE *fin;   // указатель на файл данных
   char filename[256];
   double *array;
   double amin, amax;
   size_t arrayLength;
   int errcode;

   // имя файла с данными
   printf("data file name >");
   if (scanf("%s", filename) != 1) {
      printf("Error reading data filename\n");
      return -1; 
   }   // не самый хороший способ, но пусть пока так

   // доступ к файлу
   fin = fopen(filename, "r");
   if (!fin) {
      printf("Error opening file %s\n", filename);
      return -1; 
   }

   // чтение и создание массива данных (отдельная функция)
   array = ReadArrayCnt(fin, &arrayLength, &errcode);
   //array = ReadArrayNum(fin, &arrayLength, &errcode);
   
   // файл прочитали, он больше не нужен
   fclose(fin);

   // тестовая печать 
   if (array) {
      printf("Array length = %lu\n", (unsigned long)arrayLength);
      PrintArray(stdout, array, arrayLength, "Array from file");
   } else {
      switch(errcode) {
      case -1:
         printf("file is not opened\n");
         break;
      case -2:
         printf("no numbers in file\n");
         break;
      case -3:
         printf("memory allocation error\n");
         break;
      case -4:
         printf("rereading error\n");
         break;
      }
      return -1; 
   }

   // обработка массива 
   MinMax(array, arrayLength, &amin, &amax);

   // вывод результата
   printf("min = %f  max = %f\n",amin, amax);

   // освобождение захваченных ресурсов
   free(array);


   // тест с генерацией массива
   arrayLength = 20;
   array = GenerateArray(arrayLength);
   if (!array) {
      printf("array generation error: size-%lu\n", (unsigned long)arrayLength);
      return -1;
   }
   MinMax(array, arrayLength, &amin, &amax);
   PrintArray(stdout, array, arrayLength, "Generated array");
   printf("min = %f  max = %f\n",amin, amax);
   free(array);

   return 0;
}


