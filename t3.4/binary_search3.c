#include "binary_search.h"


// Обобщенная функция для бинарного поиска подходящего места для вставки элемента
int binary_search3(void *base, size_t left, size_t right, size_t i, size_t elementSize, void *key, int (*comparator)(const void *, const void *)) {
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        void *midPtr = (char *)base + mid * elementSize;
        int cmpResult = comparator(midPtr, key);
        if (i == 0) {return i;}
        printf("mid = %ld\n", mid);
        printf("cmpResult = %d\n", cmpResult);
        printf("left = %ld\n", left);
        printf("right = %ld\n", right);
        if (cmpResult == 0) {
            return mid;
        } else if (cmpResult < 0) {
            left = mid;
            left++;
        } else {
            //if (i == 1) {return 0;}
            right = mid;
            right--;
            if (right == (long unsigned int)(- 1)) {return 0;}
        }
        printf("left = %ld\n", left);
        printf("right = %ld\n", right);
    }
    return left;
}