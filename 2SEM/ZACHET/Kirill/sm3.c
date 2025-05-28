#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_COLUMNS 50
#define MAX_LINE_LENGTH 1024
#define EPS 1e-15

int main(void) {
    FILE *in, *out;
    char line[MAX_LINE_LENGTH];
    char column_name[MAX_LINE_LENGTH];
    int pos;
    char *token;
    int count = 0;
    double target = 0;
    int check = 0;
    char *endptr;
    double numbers[MAX_COLUMNS];
    char *column_names[MAX_COLUMNS];

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

    // Записываем заголовки в выходной файл
    for (int i = 0; i < count; i++) {
        fprintf(out, "%s", column_names[i]);
        if (i < count - 1) fprintf(out, "\t");
    }
    fprintf(out, "\n");
    
    for (int i = 0; i < count; i++) {
        free(column_names[i]);
    }


    // обработка строк данных
    while(fgets(line, MAX_LINE_LENGTH, in) != NULL) {
        check = 0;
        count = 0;
        //fgets(line, sizeof(line), in);
        // Разбиваем строку на числа
        token = strtok(line, " \t\n");
        while (token != NULL && count < MAX_COLUMNS) {
            numbers[count] = strtod(token, &endptr);
            
            if (endptr == token) {
                printf("Ошибка: '%s' не является числом\n", token);
                return -1;
            }
            count++;
            token = strtok(NULL, " \t\n");
        }
        target = numbers[pos];
        //printf("%lf\n", numbers[0]);
        // проверяем остальные числа на совпадение
        for (int i = 0; i < count; i++) {
            if (i != pos && fabs(numbers[i] - target) < EPS) {
                check = 1;
                break;
            }
        }

        if (!check) {
            for (int i = 0; i < count; i++) {
                fprintf(out, "%lf", numbers[i]);
                if (i < count - 1) fprintf(out, "\t");
            }
            fprintf(out, "\n");
        }
    }

    fclose(in);
    fclose(out);
    return 0;
}