#include "3.13.h"
//#define TestBit(x, bit) ((x >> bit) & 1)

// Функция сравнения двух int чисел для qsort
int CmpInt(const void *a, const void *b) {
    const int *pa = (const int *)a;
    const int *pb = (const int *)b;
    return (*pa < *pb) ? -1 : (*pa > *pb) ? 1 : 0;
}

// Функция для проверки последовательности на возрастание
bool TestSort(long long int n, unsigned int *arr) {
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

/* 
int QuickBitSortPartition(unsigned int *arr, int low, int high, int ascending) {
    unsigned int pivot = arr[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;

    while (1) {
        if (ascending) {
            while (arr[++i] < pivot);  // Перемещаем i вперед, пока не найдем элемент >= pivot
            while (arr[--j] > pivot);  // Перемещаем j назад, пока не найдем элемент <= pivot
        } else {
            while (arr[++i] > pivot);  // Перемещаем i вперед, пока не найдем элемент <= pivot
            while (arr[--j] < pivot);  // Перемещаем j назад, пока не найдем элемент >= pivot
        }


        if (i >= j)
            return j;

        Swap(arr[i], arr[j]);
    }
}

void QuickSort(unsigned int *arr, int low, int high, int ascending) {
    if (low < high) {
        int pivot = QuickBitSortPartition(arr, low, high, ascending);
        QuickSort(arr, low, pivot, ascending);
        QuickSort(arr, pivot + 1, high, ascending);
    }
}
 */
// Основная функция разбиения
long long int QuickBitSortPartition(long long int n, unsigned int *a, int ibit, int asceding) {
    int i, j;

    while (true) {
        if (asceding) { // По возрастанию
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
        } else {
            return j + 1;
        } 
    }
}

// Рекурсивная функция для быстрой сортировки
void QuickBitSort(long long int n, unsigned int *a, int bit, int asceding) {
    long long int pivot;
    if (n < 2) {
        //QuickBitSort(n, a, bit, asceding);
        return;
    }
    pivot = QuickBitSortPartition(n, a, bit, asceding);
    printf("pivot %lld\n", pivot);
    if (pivot < n - pivot) {
        QuickBitSort(pivot, a, bit, asceding);
        //QuickBitSort(n - pivot, a + pivot, bit, asceding);
    } else {
        QuickBitSort(n - pivot, a + pivot, bit, asceding);
        //QuickBitSort(pivot, a, bit, asceding);
    }
}
/* 
// Основная функция разбиения
long long int QuickBitSortPartition2(long long int n, unsigned int *a, int asceding) {
    int i, j;
    int ibit = (a[0] - a[n - 1]) / 2;
    while (true) {
        if (asceding) { // По возрастанию
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
        } else {
            return j + 1;
        } 
    }
}

void QuickBitSort2(long long int n, unsigned int* a,int asceding) {
    int k;
    while (n > 1) {
        k = QuickBitSortPartition2(n, a, asceding);
        if (k < n - k) {
            QuickBitSort2(k, a, asceding);
            a = a + k;
            n = n - k;
        } else {
            QuickBitSort2(n - k, a + k, asceding);
            n = k;
        }
    }
} */
/* 
// Быстрая сортировка
void QuickBitSort(long long int n, unsigned int* a, int ibit, int ascending) {
    int k;
    if (n < 2) {
        return;
    }
    
    k = QuickBitSortPartition(n, a, ibit, ascending);
    //printf("%d\n", k);
    if (k < n - k) {
        QuickBitSort(k, a, ibit, ascending);
        QuickBitSort(n - k, a + k, ibit, ascending);
    } else {
        QuickBitSort(n - k, a + k, ibit, ascending);
        QuickBitSort(k, a, ibit, ascending);
    }
}
 */

 










/* 
// Основная функция разбиения
int QuickBitSortPartition(long long int n, unsigned int *a, int ibit, int asceding) {
    int i, j;
    
    if (n <= 1) {
        return 0; // Граничный случай: пустой массив или массив с одним элементом
    }

    if (asceding == 0) { // По возрастанию
        for (i = 0; i < n && !TestBit(a[i], ibit); i++) {}
        for (j = n - 1; j >= 0 && TestBit(a[j], ibit); j--) {}
    } else { // По убыванию
        for (i = 0; i < n && TestBit(a[i], ibit); i++) {}
        for (j = n - 1; j >= 0 && !TestBit(a[j], ibit); j--) {}
    }

    if (i >= j) {
        return j;
    }

    Swap(&a[i], &a[j]);
    ++i, --j;

    return j;
}

// Рекурсивная функция для быстрой сортировки
void QuickBitSort(long long int n, unsigned int *a, int bit, int asceding) {
    long long int pivot;
    if (n <= 1 || bit >= 32) {
        return; // Граничный случай: пустой массив, массив с одним элементом или исчерпаны все биты
    }

    pivot = QuickBitSortPartition(n, a, bit, asceding);
    if (pivot > 0) {
        QuickBitSort(pivot, a, bit + 1, asceding);
    }
    if (pivot < n - 1) {
        QuickBitSort(n - pivot - 1, a + pivot + 1, bit + 1, asceding);
    }
} */