#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 8
#define MAX_WORDS 50

void Alphabet(FILE *file);
int Compare(const void *a, const void *b);
void Alphabet2(FILE *file);
int Compare2(const void *a, const void *b);


// Функция сравнения с учетом регистра
int Compare(const void *a, const void *b) {
    return strcmp((const char *)a, (const char *)b);
}


// Функция сравнения без учёта регистра
int Compare2(const void *a, const void *b) {
    return strcasecmp((const char *)a, (const char *)b);
}


void Alphabet(FILE *file) {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;
    char current_word[MAX_WORD_LENGTH];
    int char_pos = 0;
    int c;
    bool exists = false;
    bool word_too_long = false;

    while ((c = fgetc(file)) != EOF && word_count < MAX_WORDS) {
        if (isalpha(c)) {
            if (char_pos < MAX_WORD_LENGTH - 1) {
                current_word[char_pos++] = c;
            } 
            else if (!word_too_long) {
                // обнаружено слишком длинное слово
                word_too_long = true;
                fprintf(stderr, "Внимание: количество букв в слове больше допустимых %d символов\n", 
                        MAX_WORD_LENGTH-1);
            }
        } 
        else {
            if (char_pos > 0) {
                current_word[char_pos] = '\0';
                char_pos = 0;

                // добавляем только корректные слова
                if (!word_too_long) {
                    exists = false;
                    for (int i = 0; i < word_count; i++) {
                        if (strcmp(words[i], current_word) == 0) {
                            exists = true;
                            break;
                        }
                    }

                    if (!exists) {
                        strcpy(words[word_count++], current_word);
                    }
                }
                word_too_long = false; // сброс флага для следующего слова
            }
        }
    }

    // Обработка последнего слова в файле
    if (char_pos > 0 && !word_too_long && word_count < MAX_WORDS) {
        current_word[char_pos] = '\0';
        exists = false;
        for (int i = 0; i < word_count; i++) {
            if (strcmp(words[i], current_word) == 0) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            strcpy(words[word_count++], current_word);
        }
    }

    // Сортировка и вывод
    qsort(words, word_count, MAX_WORD_LENGTH, Compare);
    
    printf("Уникальные слова в алфавитном порядке с учётом регистра:\n");
    for (int i = 0; i < word_count; i++) {
        printf("%s\n", words[i]);
    }
}


void Alphabet2(FILE *file) {
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int word_count = 0;
    char current_word[MAX_WORD_LENGTH];
    int char_pos = 0;
    int c;
    bool exists = false;
    bool word_too_long = false;

    while ((c = fgetc(file)) != EOF && word_count < MAX_WORDS) {
        if (isalpha(c)) {
            if (char_pos < MAX_WORD_LENGTH - 1) {
                current_word[char_pos++] = tolower(c);
            } 
            else if (!word_too_long) {
                // обнаружено слишком длинное слово
                word_too_long = true;
                fprintf(stderr, "Внимание: количество букв в слове больше допустимых %d символов\n", 
                        MAX_WORD_LENGTH-1);
            }
        } 
        else {
            if (char_pos > 0) {
                current_word[char_pos] = '\0';
                char_pos = 0;

                // добавляем только корректные слова
                if (!word_too_long) {
                    exists = false;
                    for (int i = 0; i < word_count; i++) {
                        if (strcasecmp(words[i], current_word) == 0) {
                            exists = true;
                            break;
                        }
                    }

                    if (!exists) {
                        strcpy(words[word_count++], current_word);
                    }
                }
                word_too_long = false; // сброс флага для следующего слова
            }
        }
    }

    // Обработка последнего слова в файле
    if (char_pos > 0 && !word_too_long && word_count < MAX_WORDS) {
        current_word[char_pos] = '\0';
        exists = false;
        for (int i = 0; i < word_count; i++) {
            if (strcasecmp(words[i], current_word) == 0) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            strcpy(words[word_count++], current_word);
        }
    }

    // Сортировка и вывод
    qsort(words, word_count, MAX_WORD_LENGTH, Compare2);
    
    printf("Уникальные слова в алфавитном порядке без учёта регистра:\n");
    for (int i = 0; i < word_count; i++) {
        printf("%s\n", words[i]);
    }
}


int main(void) {
    FILE *in;
    int check = 0;

    if ((in = fopen("input.txt", "r")) == NULL) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    printf("1 / 2: ");
    scanf("%d", &check);
    printf("check %d\n", check);
    if (check == 1) Alphabet(in);
    else if (check == 2) Alphabet2(in);
    else fprintf(stderr, "check != 1 or 2\n");

    fclose(in);
    return 0;
}
