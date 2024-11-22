#include "3.13.h"

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

// Функция для обмена двух значений
void swap(unsigned int *a, unsigned int *b)
{
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
}

// Функция для получения значения k-го бита числа num
int get_kth_bit(unsigned int num, int k)
{
    return ((num >> k) & 1);
}

// Быстрая сортировка с использованием k-го бита
void bit_quick_sort(unsigned int arr[], int low, int high, int k)
{
    int pivot, i, j;
    if (low >= high || k < 0) {
        return;
    }
    
    // Выбираем опорный элемент как средний элемент
    pivot = get_kth_bit(arr[(low + high) / 2], k);
    i = low, j = high;
    
    while (i <= j) {
        while (get_kth_bit(arr[i], k) < pivot) {
            i++;
        }
        
        while (get_kth_bit(arr[j], k) > pivot) {
            j--;
        }
        
        if (i <= j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    
    // Рекурсивная сортировка частей массива
    bit_quick_sort(arr, low, j, k - 1);   // Левая часть
    bit_quick_sort(arr, i, high, k - 1);  // Правая часть
}