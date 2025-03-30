#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool CheckBit(int num, int m);
void BitMatrix(int **matrix, int rows, int *cols, int M, int N);
int MaxNumberLength(int **matrix, int rows, int cols);


// Функция, которая принимает значение 1, если m бит == 0, иначе — значение 0
bool CheckBit(int num, int m) {
    return !(num & (1 << (m - 1)));
}


// Функция для определения максимальной длины числа в столбце
int MaxNumberLength(int **matrix, int rows, int cols) {
    int max_len = 0, current_len, i, j;
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            current_len = snprintf(NULL, 0, "%d", matrix[i][j]);
            if (current_len > max_len) {
                max_len = current_len;
            }
        }
    }
    return max_len;
}


// Функция для обработки матрицы
void BitMatrix(int **matrix, int rows, int *cols, int M, int N) {
    // Создаем массив для отметки столбцов, которые нужно сохранить
    bool *keep_column = (bool *)malloc(*cols * sizeof(bool));
    int new_cols = 0;
    bool all_zero;
    int i, j;
    int current_group_size = 0;
    int **new_matrix;
    int new_j;
    int num_width;
    
    // Первый проход: находим столбцы, где у всех элементов M-й бит равен 0
    for (j = 0; j < *cols; j++) {
        all_zero = true;
        for (i = 0; i < rows; i++) {
            if (!CheckBit(matrix[i][j], M)) {
                all_zero = false;
                break;
            }
        }
        keep_column[j] = all_zero;
    }
    
    // Второй проход: обрабатываем группы последовательных столбцов
    for (j = 0; j < *cols; j++) {
        if (keep_column[j]) {
            current_group_size++;
            if (current_group_size > N) {
                keep_column[j] = false;
            }
        } else {
            current_group_size = 0;
        }
    }
    
    // Подсчитываем количество столбцов для новой матрицы
    new_cols = 0;
    for (j = 0; j < *cols; j++) {
        if (keep_column[j] || !CheckBit(matrix[0][j], M)) {
            new_cols++;
        }
    }
    
    // Создаем новую матрицу
    new_matrix = (int **)malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        new_matrix[i] = (int *)malloc(new_cols * sizeof(int));
        new_j = 0;
        for (j = 0; j < *cols; j++) {
            if (keep_column[j] || !CheckBit(matrix[i][j], M)) {
                new_matrix[i][new_j++] = matrix[i][j];
            }
        }
    }
    
    // Освобождаем память старой матрицы
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    // Заменяем старую матрицу новой
    matrix = new_matrix;
    *cols = new_cols;
    free(keep_column);
    
    // Определяем максимальную длину числа для форматирования
    num_width = MaxNumberLength(new_matrix, rows, new_cols) + 1;

    // Выводим результат
    printf("Обработанная матрица (%d x %d):\n", rows, *cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < *cols; j++) {
            printf("%*d", num_width, matrix[i][j]);
        }
        free(matrix[i]);
        printf("\n");
    }
    free(matrix);
}


int main(void) {
    int rows, cols, M, N;
    int **matrix;
    FILE *in;
    int i, j;

    if ((in = fopen("input.txt", "r"))==NULL) {
        printf("input.txt error\n");
        return -1;
    }
    
    //printf("Введите количество строк и столбцов матрицы: ");
    fscanf(in, "%d %d", &rows, &cols);
    
    //printf("Введите M и N: ");
    fscanf(in, "%d %d", &M, &N);
    
    // Выделение памяти и ввод матрицы
    matrix = (int **)malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        //printf("Введите строку %d: ", i + 1);
        for (j = 0; j < cols; j++) {
            fscanf(in, "%d", &matrix[i][j]);
        }
    }
    
    BitMatrix(matrix, rows, &cols, M, N);
    
    // Освобождение памяти
/*     for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix); */
    
    return 0;
}