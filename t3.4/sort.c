#include "sort.h"
#include "binary_search.h"

// Функция для реализации сортировки просеиванием с бинарным поиском
void insertion_sort_with_binary_search(double arr[], int n)
{
    for (int i = 1; i < n; ++i) {
        double key = arr[i];
        int pos = binary_search(arr, 0, i - 1, key);
        
        // Перемещаем элементы вправо, чтобы освободить место для вставляемого элемента
        for (int j = i; j > pos; --j) {
            arr[j] = arr[j - 1];
        }
        
        // Вставляем ключ в нужную позицию
        arr[pos] = key;
    }
}