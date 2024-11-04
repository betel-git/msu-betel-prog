#include "t3.4.h"

// Функция для выполнения бинарного поиска позиции вставки элемента
int BinSearch(double arr[], int left, int right, double key)
{
    while (left <= right) {
        int mid = left + (right - left) / 2;
        double eps = 0.000001;
        if (fabs(arr[mid] - key) < eps) {
            return mid;
        }
        else if (arr[mid] > key) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    
    // Если элемент не найден, возвращаем позицию, где он должен быть вставлен
    return left;
}

// Функция для выполнения бинарного поиска позиции вставки элемента
int BinSearch2(double arr[], int left, int right, double key, int (*cmp)(double, double))
{
    while (left <= right) {
        int mid = left + (right - left) / 2;
        double eps = 0.000001;
        if (fabs(arr[mid] - key) < eps) {
            return mid;
        }
        else if (cmp(arr[mid], key) > 0) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    
    // Если элемент не найден, возвращаем позицию, где он должен быть вставлен
    return left;
}


// Обобщенная функция для бинарного поиска подходящего места для вставки элемента
int BinSearch3(void *base, size_t left, size_t right, size_t i, size_t elementSize, void *key, int (*cmp)(const void *, const void *)) {
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        void *midPtr = (char *)base + mid * elementSize;
        int cmpResult = cmp(midPtr, key);
        if (i == 0) {return i;}
        if (cmpResult == 0) {
            return mid;
        } else if (cmpResult < 0) {
            left = mid;
            left++;
        } else {
            right = mid;
            right--;
            if (right == (long unsigned int)(- 1)) {return 0;}
        }
    }
    return left;
}