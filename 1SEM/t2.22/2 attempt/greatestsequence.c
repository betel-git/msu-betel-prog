
#include <stdio.h>
#include "greatestsequence.h"

// Функция для поиска максимального возрастающего участка
int find_max_segment(int *arr, int size) {
    int count = 0;
    int res = 0;
    int boolean = 0;
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] <= arr[i + 1]) {
            count += 1;
            if (boolean) {
                count += 1;
                boolean = 0;
            }
            if (i == 0) {
                count += 1;
            }
        }
        else {
            if (count >= res) {
                res = count;
            }
            count = 0;
            boolean = 1;
        }
        fprintf(stdout, "current %i\n", arr[i + 1]);
        fprintf(stdout, "count %i\n", count);
        fprintf(stdout, "res %i\n", res);
        fprintf(stdout, "bool %i\n", boolean);
    }
    if (count >= res) {
        res = count;
    }
    return res;
}
