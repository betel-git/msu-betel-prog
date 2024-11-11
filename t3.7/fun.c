#include "3.7.h"

// Функция для проверки последовательности на возрастание
bool TestSort(int n, double *arr) {
    int i;
    for (i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        };
    }
    return true;
}

// Функция сравнения для double переменных
int CmpDouble(const void *a, const void *b) {
    const double *pa = (const double *)a;
    const double *pb = (const double *)b;
    return (*pa < *pb) ? -1 : (*pa > *pb) ? 1 : 0;
}

int Compare(double a, double b) {
    return (a < b) ? -1 : (a > b) ? 1 : 0;
}


// Функция для слияния двух отсортированных частей массива
void Merge1(double arr[], int left, int mid, int right, double temp[]) {
    int i = left;      // Индекс левой части
    int j = mid + 1;   // Индекс правой части
    int k = left;      // Индекс временного массива

    // Слияние двух частей массива
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Копирование оставшихся элементов левой части
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Копирование оставшихся элементов правой части
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Копирование отсортированного массива обратно в исходный массив
    for (int l = left; l <= right; l++) {
        arr[l] = temp[l];
    }
}

// Функция для слияния двух отсортированных частей массива
void Merge2(double arr[], int left, int mid, int right, double temp[]) {
    int i = left;      // Индекс левой части
    int j = mid + 1;   // Индекс правой части
    int k = left;      // Индекс временного массива

    // Слияние двух частей массива
    while (i <= mid && j <= right) {
        if (Compare(arr[i], arr[j]) <= 0) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    // Копирование оставшихся элементов левой части
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Копирование оставшихся элементов правой части
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Копирование отсортированного массива обратно в исходный массив
    for (int l = left; l <= right; l++) {
        arr[l] = temp[l];
    }
}


// Функция для слияния двух отсортированных частей массива
void Merge3(void* arr, int left, int mid, int right, size_t elem_size, int (*cmp)(const void *, const void *)) {
    int len = right - left + 1;     // Длина результирующего массива
    char *temp = malloc(len * elem_size);  // Временный массив

    int i = left;                    // Индекс левой части
    int j = mid + 1;                 // Индекс правой части
    int k = 0;                       // Индекс временного массива

    // Слияние двух частей массива
    while (i <= mid && j <= right) {
        if (cmp((char*)arr + i * elem_size, (char*)arr + j * elem_size) <= 0) {
            memcpy(temp + k * elem_size, (char*)arr + i * elem_size, elem_size);
            i++;
        } else {
            memcpy(temp + k * elem_size, (char*)arr + j * elem_size, elem_size);
            j++;
        }
        k++;
    }

    // Копирование оставшихся элементов левой части
    while (i <= mid) {
        memcpy(temp + k * elem_size, (char*)arr + i * elem_size, elem_size);
        i++; k++;
    }

    // Копирование оставшихся элементов правой части
    while (j <= right) {
        memcpy(temp + k * elem_size, (char*)arr + j * elem_size, elem_size);
        j++; k++;
    }

    // Копирование отсортированного массива обратно в исходный массив
    memcpy((char*)arr + left * elem_size, temp, len * elem_size);
    
    free(temp);  // Освобождаем память, выделенную под временный массив
}


// Итерационная реализация сортировки слиянием
void MergeSortIterative1(double arr[], int n) {
    int width = 1;  // Начальная ширина интервала слияния
    double *temp = (double *)malloc(n * sizeof(double));  // Дополнительная память для временного массива
    
    if (!temp) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    while (width < n) {
        int i;
        
        for (i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = i + 2 * width - 1;
            
            // Обработка границы массива
            if (mid >= n)
                mid = n - 1;
            if (right >= n)
                right = n - 1;
                
            Merge1(arr, left, mid, right, temp);
        }
        
        width *= 2;  // Увеличиваем ширину интервала
    }

    free(temp);  // Освобождаем выделенную память
}

// Итерационная реализация сортировки слиянием
void MergeSortIterative2(double arr[], int n) {
    int width = 1;  // Начальная ширина интервала слияния
    double *temp = (double *)malloc(n * sizeof(double));  // Дополнительная память для временного массива
    
    if (!temp) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    while (width < n) {
        int i;
        
        for (i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = i + 2 * width - 1;
            
            // Обработка границы массива
            if (mid >= n)
                mid = n - 1;
            if (right >= n)
                right = n - 1;
                
            Merge2(arr, left, mid, right, temp);
        }
        
        width *= 2;  // Увеличиваем ширину интервала
    }

    free(temp);  // Освобождаем выделенную память
}

void MergeSortIterative3(void *arr, int n, size_t elementSize, int(*cmp)(const void *, const void *)) {
    int width = 1;  // Начальная ширина интервала слияния

    while (width < n) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = i + 2 * width - 1;
            
            // Обработка границы массива
            if (mid >= n)
                mid = n - 1;
            if (right >= n)
                right = n - 1;
                
            Merge3(arr, left, mid, right, elementSize, cmp);
        }
        
        width *= 2;  // Увеличиваем ширину интервала
    }
}