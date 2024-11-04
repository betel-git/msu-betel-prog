#include "sort.h"
#include "binary_search.h"


void insertion_sort_with_binary_search3(void *base, size_t numElements, size_t elementSize, int (*comparator)(const void *, const void *)) {
    for (size_t i = 0; i < numElements; i++) {
        size_t pos = 0;
        void *key = (char *)base + i * elementSize;       // Элемент, который нужно вставить
        printf("\ni = %ld\n", i);
        pos = binary_search3(base, 0, i, i, elementSize, key, comparator);
        printf("pos = %ld\n", pos);
        
        
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
