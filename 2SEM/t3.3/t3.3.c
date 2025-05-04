#include <stdio.h>
#include <string.h>
//#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 10

void Replace(FILE *in, FILE *out, char *from, char *to);


void Replace(FILE *in, FILE *out, char *from, char *to) {
    int fromlen = strlen(from);
    int tolen = strlen(to);
    char *buffer;
    int i = 0, j, k, l;
    char c;

    if (fromlen == 0) return;
    buffer = malloc(fromlen);
    if (!buffer) {
        perror("Ошибка выделения памяти");
        return;
    }
    while ((c = fgetc(in)) != EOF) {
        buffer[i] = c;
        i++;
        if (c == from[i - 1]) {
            if (i == fromlen) {
                fwrite(to, 1, tolen, out);
                i = 0;
            }
        }
        else {
            fputc(buffer[0], out);
            k = 0; // номер буквы в слове, которое меняем
            j = 1; // номер буквы в буфере
            l = 1; // номер буквы, с которой начинаем проверку буфера на наличие начала нужной строки
            while (j < i) {
                if (buffer[j] == from[k]) {
                    k++, j++;
                }
                else {
                    k = 0;
                    fputc(buffer[l], out); // выбрасываем данную букву
                    j = l + 1; // начинаем поиск с l + 1 буквы слова из буфера
                    l++;
                }
            }
            if (l == i) i = 0;
            else {
                for (j = 0; j + l < i; j++) { // сдвигаем все элементы буфера на нужное количество букв
                    buffer[j] = buffer[j + l];
                }
                i = j;
            }
        }
    }
    if (i > 0) {
        fwrite(buffer, 1, i, out);
    }
    free(buffer);
}


int main(void) {
    FILE *in, *out;
    char from[MAX_LINE_LENGTH], to[MAX_LINE_LENGTH];
    int input_ok = 1;


    if ((in = fopen("input.txt", "r")) == NULL) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    if ((out = fopen("output.txt", "w")) == NULL) {
        perror("Ошибка открытия выходного файла");
        fclose(in);
        return -1;
    }

    printf("Введите строку, которую нужно заменить: ");
    if (fgets(from, sizeof(from), stdin) == NULL) {
        perror("Ошибка ввода");
        fclose(in), fclose(out);
        return -1;
    }

    // Проверка на переполнение буфера
    if (strchr(from, '\n') == NULL) {
        fprintf(stderr, "Ошибка: введенная строка слишком длинная (максимум %d символов)\n", 
                MAX_LINE_LENGTH - 1);
        input_ok = 0;
        // Очистка буфера stdin
        while (fgetc(stdin) != '\n' && !feof(stdin));
    }
    else {
        from[strcspn(from, "\n")] = '\0';
    }

    if (input_ok) {
        printf("Введите строку для замены: ");
        if (fgets(to, sizeof(to), stdin) == NULL) {
            perror("Ошибка ввода");
            fclose(in);
            fclose(out);
            return -1;
        }
        
        if (strchr(to, '\n') == NULL) {
            fprintf(stderr, "Ошибка: строка замены слишком длинная (максимум %d символов)\n",
                    MAX_LINE_LENGTH - 1);
            input_ok = 0;
            while (fgetc(stdin) != '\n' && !feof(stdin));
        }
        else {
            to[strcspn(to, "\n")] = '\0';
        }
    }

    if (input_ok) {
        Replace(in, out, from, to);
        printf("Success\n");
    }
    else {
        fprintf(stderr, "Операция отменена из-за ошибок ввода\n");
    }

    fclose(in), fclose(out);
    return 0;
}
