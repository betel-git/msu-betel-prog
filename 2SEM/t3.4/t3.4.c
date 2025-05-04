#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 11

void FindWordInLine(const char *line, const char *word, int line_num);


// Функция для поиска слова в строке и вывода позиций
void FindWordInLine(const char *line, const char *word, int line_num) {
    int line_len = strlen(line);
    int word_len = strlen(word);
    int pos = 0;

    while (pos <= line_len - word_len) {
        // проверяем, является ли текущая позиция началом слова
        if ((pos == 0 || !isalpha(line[pos - 1])) &&  // перед словом не буква
            strncmp(&line[pos], word, word_len) == 0 &&  // совпадение подстроки
            //strncasecmp(&line[pos], word, word_len) == 0 &&  // совпадение подстроки (без учёта регистра)
            (pos + word_len == line_len || !isalpha(line[pos + word_len]))) {  // после слова не буква
            printf("Слово \"%s\" найдено в строке %d, позиция %d\n", word, line_num, pos + 1);
            pos += word_len;  // пропускаем найденное слово
        } else {
            pos++;
        }
    }
}


int main(void) {
    FILE *in;
    char line[MAX_LINE_LENGTH];
    int line_num = 1;
    char word[MAX_LINE_LENGTH];
    int input_ok = 1;


    if ((in = fopen("input.txt", "r")) == NULL) {
        perror("Ошибка открытия входного файла");
        return -1;
    }
    printf("Введите слово, которое нужно найти: ");
    if (fgets(word, sizeof(word), stdin) == NULL) {
        perror("Ошибка ввода");
        return -1;
    }

    // Проверка на переполнение буфера
    if (strchr(word, '\n') == NULL) {
        fprintf(stderr, "Ошибка: введенная строка слишком длинная (максимум %d символов)\n", MAX_LINE_LENGTH - 1);
        input_ok = 0;
        // Очистка буфера stdin
        while (fgetc(stdin) != '\n' && !feof(stdin));
    }
    else {
        word[strcspn(word, "\n")] = '\0';
    }

    if (input_ok) {
        while (fgets(line, sizeof(line), in)) {
            FindWordInLine(line, word, line_num);
            line_num++;
        }
        printf("Success\n");
    }
    else {
        fprintf(stderr, "Операция отменена из-за ошибок ввода\n");
    }

    fclose(in);
    return 0;
}
