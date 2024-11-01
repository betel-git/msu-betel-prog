#include "binary_search.h"

// Функция для выполнения бинарного поиска позиции вставки элемента
int binary_search2(double arr[], int left, int right, double key, int (*cmp)(double, double))
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