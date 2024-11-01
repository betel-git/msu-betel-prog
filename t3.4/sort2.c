#include "sort.h"
#include "binary_search.h"

int Compare(double a, double b);

int Compare(double a, double b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}

// Функция для реализации сортировки просеиванием с бинарным поиском
void insertion_sort_with_binary_search2(double arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        double key = arr[i];
        int pos = binary_search2(arr, 0, i - 1, key, Compare);
        
        // Перемещаем элементы вправо, чтобы освободить место для вставляемого элемента
        for (int j = i; j > pos; --j) {
            arr[j] = arr[j - 1];
        }
        
        // Вставляем ключ в нужную позицию
        arr[pos] = key;
    }
}