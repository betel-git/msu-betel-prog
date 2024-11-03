#include "sort.h"
#include "binary_search.h"


void insertion_sort_with_binary_search3(void *base, size_t numElements, size_t elementSize, int (*comparator)(const void *, const void *)) {
    for (size_t i = 1; i < numElements; i++) {
        void *key = (char *)base + i * elementSize;       // Элемент, который нужно вставить
        size_t pos = binary_search3(base, 0, i - 1, elementSize, key, comparator);
        
        // Перемещаем элементы вправо, чтобы освободить место для вставляемого элемента
        for (size_t j = i; j > pos; --j) {
            memcpy((char *)base + j * elementSize, (char *)base + (j - 1) * elementSize, elementSize);
        }
        
        // Вставляем ключ в нужную позицию
        memcpy((char *)base + pos * elementSize, key, elementSize);
    }
}
