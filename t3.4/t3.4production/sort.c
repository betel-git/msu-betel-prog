#include "t3.4.h"

// Функция для реализации сортировки просеиванием с бинарным поиском
void InsertionSortWithBinSearch1(double arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        double key = arr[i];
        int pos = BinSearch(arr, 0, i - 1, key);
        
        // Перемещаем элементы вправо, чтобы освободить место для вставляемого элемента
        for (int j = i; j > pos; --j) {
            arr[j] = arr[j - 1];
        }
        
        // Вставляем ключ в нужную позицию
        arr[pos] = key;
    }
}

int Compare(double a, double b);

int Compare(double a, double b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}

// Функция для реализации сортировки просеиванием с бинарным поиском
void InsertionSortWithBinSearch2(double arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        double key = arr[i];
        int pos = BinSearch2(arr, 0, i - 1, key, Compare);
        
        // Перемещаем элементы вправо, чтобы освободить место для вставляемого элемента
        for (int j = i; j > pos; --j) {
            arr[j] = arr[j - 1];
        }
        
        // Вставляем ключ в нужную позицию
        arr[pos] = key;
    }
}

void InsertionSortWithBinSearch3(void *base, size_t numElements, size_t elementSize, int (*cmp)(const void *, const void *)) {
    for (size_t i = 0; i < numElements; i++) {
        size_t pos = 0;
        void *key = (char *)base + i * elementSize;       // Элемент, который нужно вставить
        //printf("\ni = %ld\n", i);
        pos = BinSearch3(base, 0, i, i, elementSize, key, cmp);
        //printf("pos = %ld\n", pos);
        
        
        // Перемещаем элементы вправо, начиная с позиции после найденной
        if (pos != i) {
            void *temp = malloc(elementSize);
            memcpy(temp, key, elementSize);
            
            memmove((char *)base + pos * elementSize + elementSize, (char *)base + pos * elementSize, (i - pos) * elementSize);
            
            memcpy((char *)base + pos * elementSize, temp, elementSize);
            free(temp);
        }
        //printf("arr = %p\n", base);
    }
}
