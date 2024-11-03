#include "binary_search.h"


// Обобщенная функция для бинарного поиска подходящего места для вставки элемента
int binary_search3(void *base, size_t left, size_t right, size_t elementSize, void *key, int (*comparator)(const void *, const void *)) {
    if (right != left) {
        while (left <= right) {
            size_t mid = left + (right - left) / 2;
            void *midPtr = (char *)base + mid * elementSize;
            
            int cmpResult = comparator(midPtr, key);
            if (cmpResult == 0) {
                return mid;
            } else if (cmpResult < 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return left;
}