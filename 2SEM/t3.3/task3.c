
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void replace_occurrences(FILE *input_file, FILE *output_file, 
    const char *search, const char *replace);

void replace_occurrences(FILE *input_file, FILE *output_file, 
                        const char *search, const char *replace) {
    //char buffer[BUFFER_SIZE];
    size_t search_len = strlen(search);
    size_t replace_len = strlen(replace);
    size_t idx = 0;
    int c;

    while ((c = fgetc(input_file)) != EOF) {
        if (c == search[idx]) {
            idx++;
            if (idx == search_len) {
                // Полное совпадение найдено
                fwrite(replace, 1, replace_len, output_file);
                idx = 0;
            }
        } else {
            if (idx > 0) {
                // Частичное совпадение - выводим накопленные символы
                fwrite(search, 1, idx, output_file);
                idx = 0;
            }
            fputc(c, output_file);
        }
    }

    // Если остались необработанные символы после EOF
    if (idx > 0) {
        fwrite(search, 1, idx, output_file);
    }
}

int main(void) {
    FILE *in, *out;
    char from[256], to[256];


    if ((in = fopen("input.txt", "r")) == NULL) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    if ((out = fopen("output.txt", "w")) == NULL) {
        perror("Ошибка открытия выходного файла");
        return -1;
    }

    printf("Введите строку, которую нужно заменить: ");
    if (fgets(from, sizeof(from), stdin) == NULL) {
        perror("Ошибка ввода");
        return -1;
    }
    from[strcspn(from, "\n")] = '\0'; // Удаление символа новой строки

    printf("Введите строку для замены: ");
    if (fgets(to, sizeof(to), stdin) == NULL) {
        printf("Ошибка ввода.\n");
        return 1;
    }
    to[strcspn(to, "\n")] = '\0'; // Удаление символа новой строки

    replace_occurrences(in, out, from, to);

    fclose(in), fclose(out);
    printf("Success\n");
    return 0;
}
