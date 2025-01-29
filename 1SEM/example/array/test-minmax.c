// 
//  ������ ����������� ���� ��� ��������� �������
// 

// ��������� ������������ �������
#include <stdio.h>
#include <stdlib.h>

// ��������� ����� �������
#include "minmax2.h"
#include "array.h"

// ���� ��������� �������

int main(void)
{
   FILE *fin;   // ��������� �� ���� ������
   char filename[256];
   double *array;
   double amin, amax;
   size_t arrayLength;
   int errcode;

   // ��� ����� � �������
   printf("data file name >");
   if (scanf("%s", filename) != 1) {
      printf("Error reading data filename\n");
      return -1; 
   }   // �� ����� ������� ������, �� ����� ���� ���

   // ������ � �����
   fin = fopen(filename, "r");
   if (!fin) {
      printf("Error opening file %s\n", filename);
      return -1; 
   }

   // ������ � �������� ������� ������ (��������� �������)
   array = ReadArrayCnt(fin, &arrayLength, &errcode);
   //array = ReadArrayNum(fin, &arrayLength, &errcode);
   
   // ���� ���������, �� ������ �� �����
   fclose(fin);

   // �������� ������ 
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

   // ��������� ������� 
   MinMax(array, arrayLength, &amin, &amax);

   // ����� ����������
   printf("min = %f  max = %f\n",amin, amax);

   // ������������ ����������� ��������
   free(array);


   // ���� � ���������� �������
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


