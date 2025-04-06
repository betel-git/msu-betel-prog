#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool CheckBit(int num, int m);
void BitMatrix(int **matrix, int *rows, int cols, int M, int N);
int MaxNumberLength(int **matrix, int rows, int cols);


// Функция, которая принимает значение 1, если m бит == 0, иначе — значение 0
bool CheckBit(int num, int m) {
    return !(num & (1 << (m - 1)));
}


// Функция для определения максимальной длины числа в строке
int MaxNumberLength(int **matrix, int rows, int cols) {
    int max_len = 0, current_len, i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            current_len = snprintf(NULL, 0, "%d", matrix[i][j]);
            if (current_len > max_len) {
                max_len = current_len;
            }
        }
    }
    return max_len;
}


/* // Функция для обработки матрицы
void BitMatrix(int **matrix, int *rows, int cols, int M, int N) {
    // Создаем массив для отметки строк, которые нужно сохранить
    bool *keep_row1 = (bool *)malloc(*rows * sizeof(bool)); // массив для отметки строк, с элементами с нулевым M битом
    int new_rows = 0;
    bool all_zero;
    int i, j;
    int current_group_size = 0;
    int **new_matrix;
    int new_i;
    int num_width;
    
    // Первый проход: находим строки, где у всех элементов M-й бит равен 0
    for (i = 0; i < *rows; i++) {
        all_zero = true;
        for (j = 0; j < cols; j++) {
            if (!CheckBit(matrix[i][j], M)) {
                all_zero = false; // M-й бит != 0
                break;
            }
        }
        keep_row1[i] = all_zero;
    }
    
    // Второй проход: обрабатываем группы последовательных строк
    for (i = 0; i < *rows; i++) {
        if (keep_row1[i] && current_group_size < N) {
            current_group_size++;
            keep_row1[i] = false;
        } else {
            current_group_size = 0;
        }
    }
    
    // Подсчитываем количество строк для новой матрицы
    new_rows = 0;
    for (i = 0; i < *rows; i++) {
        if (!keep_row1[i]) {
            new_rows++;
        }
    }
    printf("new rows = %d\n", new_rows);
    // Создаем новую матрицу
    new_matrix = (int **)malloc(new_rows * sizeof(int *));
    for (i = 0; i < new_rows; i++) {
        new_matrix[i] = (int *)malloc(cols * sizeof(int));
        new_j = 0;
        for (j = 0; j < cols; j++) {
            if (!keep_row1[j]) {
                printf("%d\n", new_i);
                new_matrix[new_i][j] = matrix[i][j];
                new_i++;
            }
        }
    }
    printf("CHECK\n");
    // Освобождаем память старой матрицы
    for (i = 0; i < *rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    // Заменяем старую матрицу новой
    matrix = new_matrix;
    *rows = new_rows;
    free(keep_row1);
    
    // Определяем максимальную длину числа для форматирования
    num_width = MaxNumberLength(new_matrix, new_rows, cols) + 1;

    // Выводим результат
    printf("Обработанная матрица (%d x %d):\n", *rows, cols);
    for (i = 0; i < *rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%*d", num_width, matrix[i][j]);
        }
        free(matrix[i]);
        printf("\n");
    }
    free(matrix);
} */

void BitMatrix(int **matrix, int *rows, int cols, int M, int N) {
    // Создаем массив для отметки строк, которые нужно сохранить
    bool *keep_row = (bool *)malloc(*rows * sizeof(bool));
    int new_rows = 0;
    bool all_zero;
    int i, j;
    int current_group_size = 0;
    int **new_matrix;
    int num_width;
    int new_i = 0;

    // Первый проход: находим строки, где у всех элементов M-й бит равен 0
    for (i = 0; i < *rows; i++) {
        all_zero = true;
        for (j = 0; j < cols; j++) {
            if (!CheckBit(matrix[i][j], M)) {
                all_zero = false;
                break;
            }
        }
        keep_row[i] = all_zero;
    }

    // Второй проход: обрабатываем группы последовательных строк
    for (i = 0; i < *rows; i++) {
        if (keep_row[i] && current_group_size < N) {
            current_group_size++;
            keep_row[i] = false; // Помечаем для сохранения
        } else {
            if (keep_row[i]) current_group_size = 0;
        }
    }

    // Подсчитываем количество строк для новой матрицы
    new_rows = 0;
    for (i = 0; i < *rows; i++) {
        if (!keep_row[i]) {
            new_rows++;
        }
    }

    // Создаем новую матрицу правильного размера
    new_matrix = (int **)malloc(new_rows * sizeof(int *));
    for (i = 0; i < new_rows; i++) {
        new_matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Копируем нужные строки в новую матрицу
    for (i = 0; i < *rows; i++) {
        if (!keep_row[i]) {
            for (j = 0; j < cols; j++) {
                new_matrix[new_i][j] = matrix[i][j];
            }
            new_i++;
        }
    }

    // Освобождаем память старой матрицы
    for (i = 0; i < *rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    // Заменяем старую матрицу новой
    matrix = new_matrix;
    *rows = new_rows;
    free(keep_row);

    // Определяем максимальную длину числа для форматирования
    num_width = MaxNumberLength(matrix, *rows, cols) + 1;

    // Выводим результат
    printf("Обработанная матрица (%d x %d):\n", *rows, cols);
    for (i = 0; i < *rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%*d", num_width, matrix[i][j]);
        }
        printf("\n");
    }

    // Освобождаем память новой матрицы
    for (i = 0; i < *rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


int main(void) {
    int rows, cols, M, N;
    int **matrix;
    FILE *in;
    int i, j;

    if ((in = fopen("inputT.txt", "r"))==NULL) {
        printf("inputT.txt error\n");
        return -1;
    }
    
    fscanf(in, "%d %d", &rows, &cols);
    fscanf(in, "%d %d", &M, &N);
    
    // Выделение памяти и ввод матрицы
    matrix = (int **)malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            fscanf(in, "%d", &matrix[i][j]);
        }
    }
    
    BitMatrix(matrix, &rows, cols, M, N);
    
    return 0;
}