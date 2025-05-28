#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 256
#define MAX_FILES 100

void RemoveBrackets(char *str);
bool FileExists(const char *filename);

// Функция для удаления скобок вокруг имени файла
void RemoveBrackets(char *str) {
    int len = strlen(str);
    if (len > 0) {
        // Удаляем закрывающую скобку если есть
        if (str[len-1] == ')' || str[len-1] == ']' || str[len-1] == '}') {
            str[len-1] = '\0';
            len--;
        }
        // Удаляем открывающую скобку если есть
        if (len > 0 && (str[0] == '(' || str[0] == '[' || str[0] == '{')) {
            memmove(str, str+1, len);
        }
    }
}

// Функция проверки существования файла
bool FileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

int main(void) {
    char word[MAX_WORD_LENGTH];
    char cleaned_word[MAX_WORD_LENGTH];
    char *found_files[MAX_FILES];
    int file_count = 0;
    FILE *in, *out;
    bool already_added = false;

    if ((in = fopen("input.txt", "r")) == NULL) {
        return -1;
    }

    if ((out = fopen("output.txt", "w")) == NULL) {
        fclose(in);
        return -1;
    }

    // Чтение слов из входного файла
    while (fscanf(in, "%s", word) == 1) {
        strcpy(cleaned_word, word);
        RemoveBrackets(cleaned_word);

        // Проверяем, не добавляли ли мы уже этот файл
        already_added = false;
        for (int i = 0; i < file_count; i++) {
            if (strcmp(found_files[i], cleaned_word) == 0) {
                already_added = true;
                break;
            }
        }

        if (!already_added && FileExists(cleaned_word)) {
            if (file_count < MAX_FILES) {
                found_files[file_count] = strdup(cleaned_word);
                if (!found_files[file_count]) {
                    perror("Ошибка выделения памяти");
                    break;
                }
                file_count++;
            } else {
                fprintf(stderr, "Достигнуто максимальное количество файлов (%d)\n", MAX_FILES);
                break;
            }
        }
    }

    // Запись найденных файлов в выходной файл
    fprintf(out, "Найденные файлы (%d):\n", file_count);
    for (int i = 0; i < file_count; i++) {
        fprintf(out, "%s\n", found_files[i]);
        free(found_files[i]);
    }

    fclose(in);
    fclose(out);
    return 0;
}