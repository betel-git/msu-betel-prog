#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10000
#define MAX_WORD_LENGTH 100

// Функция для сравнения строк (для qsort)
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Функция для приведения слова к нижнему регистру
void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Функция для проверки, является ли символ буквой
int is_alpha_char(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Использование: %s входной_файл выходной_файл\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        perror("Не удалось открыть входной файл");
        return 1;
    }

    char *words[MAX_WORDS];
    int word_count = 0;
    char buffer[MAX_WORD_LENGTH];
    int buffer_index = 0;
    int c;

    while ((c = fgetc(input_file)) != EOF && word_count < MAX_WORDS) {
        if (is_alpha_char(c)) {
            if (buffer_index < MAX_WORD_LENGTH - 1) {
                buffer[buffer_index++] = tolower(c);
            }
        } else {
            if (buffer_index > 0) {
                buffer[buffer_index] = '\0';
                // Проверяем, нет ли уже такого слова в массиве
                int is_duplicate = 0;
                for (int i = 0; i < word_count; i++) {
                    if (strcmp(words[i], buffer) == 0) {
                        is_duplicate = 1;
                        break;
                    }
                }
                if (!is_duplicate) {
                    words[word_count] = strdup(buffer);
                    if (!words[word_count]) {
                        perror("Ошибка выделения памяти");
                        fclose(input_file);
                        return 1;
                    }
                    word_count++;
                }
                buffer_index = 0;
            }
        }
    }
    fclose(input_file);

    // Сортируем слова
    qsort(words, word_count, sizeof(char *), compare_strings);

    // Записываем результат в выходной файл
    FILE *output_file = fopen(argv[2], "w");
    if (!output_file) {
        perror("Не удалось открыть выходной файл");
        for (int i = 0; i < word_count; i++) {
            free(words[i]);
        }
        return 1;
    }

    for (int i = 0; i < word_count; i++) {
        fprintf(output_file, "%s\n", words[i]);
        free(words[i]);
    }
    fclose(output_file);

    return 0;
}