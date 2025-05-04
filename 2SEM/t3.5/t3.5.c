#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 100
#define ASCII_SIZE 128

bool IsWordChar(char c);
void AnalyzeFile(FILE *file);

// слова состоят из букв, апострофов, и дефиса
bool IsWordChar(char c) {
    return isalnum(c) || c == '\'' || c == '-';
}

void AnalyzeFile(FILE *file) {
    int wordCount = 0;
    int totalWordLength = 0;
    int maxWordLength = 0;
    int minWordLength = MAX_WORD_LENGTH;
    int charCounts[ASCII_SIZE] = {0};
    int totalChars = 0;
    int currentWordLength = 0;
    int c;
    double frequency;

    //char currentWord[MAX_WORD_LENGTH] = {0}; // на всякий случай
    //(void)currentWord; // заглушлка, чтобы скомпилировалось без unused variable

    while ((c = fgetc(file)) != EOF) {
        // подсчет частоты символов
        if (c >= 0 && c < ASCII_SIZE) {
            charCounts[(unsigned char)c]++;
            totalChars++;
        }

        // обработка слов
        if (IsWordChar(c)) {
            if (currentWordLength < MAX_WORD_LENGTH - 1) {
                //currentWord[currentWordLength] = c;
                currentWordLength++;
            }
            else {
                fprintf(stderr, "Ошибка из AnalyzeFile: слово слишком длинное (максимум %d символов)\n", MAX_WORD_LENGTH - 1);
                exit(1);
            }
        } 
        else {
            if (currentWordLength > 0) {
                //currentWord[currentWordLength] = '\0';
                wordCount++;
                totalWordLength += currentWordLength;

                if (currentWordLength > maxWordLength) {
                    maxWordLength = currentWordLength;
                }
                if (currentWordLength < minWordLength) {
                    minWordLength = currentWordLength;
                }

                currentWordLength = 0;
            }
        }
    }

    // проверяем последнее слово в файле
    if (currentWordLength > 0) {
        wordCount++;
        totalWordLength += currentWordLength;
        if (currentWordLength > maxWordLength) {
            maxWordLength = currentWordLength;
        }
        if (currentWordLength < minWordLength) {
            minWordLength = currentWordLength;
        }
    }

    // вывод результатов
    printf("Статистика анализа файла:\n");
    printf("1. Количество слов: %d\n", wordCount);
    
    if (wordCount > 0) {
        printf("2. Длина слов:\n");
        printf("   - Максимальная: %d\n", maxWordLength);
        printf("   - Минимальная: %d\n", minWordLength);
        printf("   - Средняя: %.2f\n", (float)totalWordLength / wordCount);
    } else {
        printf("2. В файле нет слов для анализа длины.\n");
    }

    printf("3. Частота символов (в %%):\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (charCounts[i] > 0 && !isspace(i) && isprint(i)) {
            frequency = (double)charCounts[i] / totalChars * 100;
            printf("   - '%c' (код %3d): %6.2f%%\n", i, i, frequency);
        }
    }

    // вывод для пробельных и управляющих символов
    printf("4. Специальные символы:\n");
    for (int i = 0; i < ASCII_SIZE; i++) {
        if (charCounts[i] > 0 && (isspace(i) || !isprint(i))) {
            frequency = (double)charCounts[i] / totalChars * 100;
            printf("   - код %3d (0x%02X): %6.2f%%\n", i, i, frequency);
        }
    }
    printf("   0x20 — пробел, 0x0A — перевод строки\n");
}


int main(void) {
    FILE *file;
    file = fopen("input.txt", "r");
    if (!file) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    AnalyzeFile(file);
    fclose(file);
    printf("Success\n");
    return 0;
}
