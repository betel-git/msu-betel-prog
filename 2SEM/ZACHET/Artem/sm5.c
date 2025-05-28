#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_COLUMNS 50
#define MAX_LINE_LENGTH 1024

int main(void) {
    FILE *in, *out;
    char line[MAX_LINE_LENGTH];
    char column_name[MAX_LINE_LENGTH];
    int pos;
    char *token;
    int count = 0;
    char *tokens[MAX_COLUMNS];
    char *current_token;
    char *column_names[MAX_COLUMNS];
    int start_col, end_col;

    if ((in = fopen("input.txt", "r")) == NULL) {
        return -1;
    }

    if ((out = fopen("output.txt", "w")) == NULL) {
        fclose(in);
        return -1;
    }

    if (fgets(line, MAX_LINE_LENGTH, in) == NULL) {
        fprintf(stderr, "Файл пуст\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    // ввод названия столбца
    printf("Введите название столбца: ");
    fgets(column_name, MAX_LINE_LENGTH, stdin);
    column_name[strcspn(column_name, "\n")] = '\0';


     // Разбиваем заголовки на столбцы
    token = strtok(line, " \t\n");
    while (token != NULL && count < MAX_COLUMNS) {
        column_names[count] = strdup(token);
        if (column_names[count] == NULL) {
            perror("Ошибка выделения памяти");
            for (int i = 0; i < count; i++) free(column_names[i]);
            fclose(in);
            fclose(out);
            return 1;
        }
        count++;
        token = strtok(NULL, " \t\n");
    }

    for (int i = 0; i < count; i++) {
        if (strcmp(column_names[i], column_name) == 0) {
            pos = i;
            break;
        }
    }


    // Определяем диапазон столбцов для сохранения
    start_col = (pos > 0) ? pos - 1 : 0;
    end_col = (pos < count - 1) ? pos + 1 : count - 1;

    // Записываем заголовки в выходной файл
    for (int i = start_col; i <= end_col; i++) {
        fprintf(out, "%s", column_names[i]);
        if (i < end_col) fprintf(out, "\t");
    }
    fprintf(out, "\n");
    

    // обработка строк данных
    while (fgets(line, MAX_LINE_LENGTH, in) != NULL) {
        count = 0;
        token = line;

        // Разбираем строку с учетом табуляции и пробелов
        while ((current_token = strtok(token, " \t\n")) != NULL && count < MAX_COLUMNS) {
            tokens[count++] = current_token;
            token = NULL; // Для последующих вызовов strtok
        }

        // Записываем только нужные столбцы
        for (int i = start_col; i <= end_col; i++) {
            fprintf(out, "%s", tokens[i]);
            if (i < end_col) fprintf(out, "\t");
        }
        fprintf(out, "\n");
    }

    // Освобождение ресурсов
    for (int i = 0; i < count; i++) {
        free(column_names[i]);
    }

    fclose(in);
    fclose(out);
    return 0;
}