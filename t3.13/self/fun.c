#include "3.13.h"

// Функция сравнения двух int чисел для qsort
int CmpInt(const void *a, const void *b) {
    const int *pa = (const int *)a;
    const int *pb = (const int *)b;
    return (*pa < *pb) ? -1 : (*pa > *pb) ? 1 : 0;
}

// Функция для проверки последовательности на возрастание
bool TestSort(int n, unsigned int *arr) {
    long long int i;
    for (i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        };
    }
    return true;
}

// Функция для проверки бита
bool TestBit(int x, int k) {
    return x & (1 << k);
}

// Обмен значений двух элементов массива
void Swap(unsigned int* a, unsigned int* b) {
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

// Функция из лекции
int QuickBitSortPartition(int n, unsigned int *a, int ibit, bool ascending) {
    int i, j;
    while(true) {
        if (ascending) { // По возрастанию
            for (i = 0; i < n && !TestBit(a[i], ibit); i++);
            for (j = n - 1; j >= 0 && TestBit(a[j], ibit); j--);
        } else { // По убыванию
            for (i = 0; i < n && TestBit(a[i], ibit); i++);
            for (j = n - 1; j >= 0 && !TestBit(a[j], ibit); j--);
        }
        if (i == n || j == -1) return 0;
        if (i < j) {
            Swap(&a[i], &a[j]);
            ++i, --j;
        } else return j + 1;
    }
}

// Рекурсивная функция быстрой сортировки по битам
void QuickBitSortRecursive(unsigned int *a, int left, int right, int maxBits, bool ascending) {
    if (left < right && maxBits >= 1) {
        int pivot = QuickBitSortPartition(right - left + 1, a + left, maxBits, ascending);
        QuickBitSortRecursive(a, left, left + pivot - 1, maxBits - 1, ascending);
        QuickBitSortRecursive(a, left + pivot, right, maxBits - 1, ascending);
    }
}

// Главная функция быстрой сортировки по битам
void QuickBitSort(unsigned int *a, int n, bool ascending) {
    int maxBits = sizeof(unsigned int) * __CHAR_BIT__;
    QuickBitSortRecursive(a, 0, n - 1, maxBits - 1, ascending);
}

// Функция для считывания массива из файла
unsigned int * ReadArrayCnt(FILE *f, int *size, int *errcode) {
    int i;    // счетчик
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
