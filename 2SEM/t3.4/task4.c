#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 100

void findWordPositions(FILE *inputFile, FILE *outputFile, const char *targetWord) {
    char line[MAX_LINE_LENGTH];
    int lineNumber = 1;
    size_t targetLen = strlen(targetWord);

    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL) {
        int posInLine = 0;
        char *ptr = line;

        while (*ptr != '\0') {
            // Пропускаем не-буквенные символы
            while (*ptr != '\0' && !isalpha((unsigned char)*ptr)) {
                ptr++;
                posInLine++;
            }

            if (*ptr == '\0') {
                break;
            }

            // Находим начало слова
            char *wordStart = ptr;
            while (*ptr != '\0' && isalpha((unsigned char)*ptr)) {
                ptr++;
            }

            // Вычисляем длину слова
            size_t wordLen = ptr - wordStart;

            // Проверяем, совпадает ли слово с искомым (без учета регистра)
            if (wordLen == targetLen && strncasecmp(wordStart, targetWord, targetLen) == 0) {
                fprintf(outputFile, "Строка %d, позиция %d\n", lineNumber, posInLine + 1);
            }

            posInLine += wordLen;
        }

        lineNumber++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Использование: %s <входной файл> <выходной файл> <слово>\n", argv[0]);
        return 1;
    }

    const char *inputFilename = argv[1];
    const char *outputFilename = argv[2];
    const char *targetWord = argv[3];

    FILE *inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        perror("Ошибка открытия входного файла");
        return 1;
    }

    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL) {
        perror("Ошибка открытия выходного файла");
        fclose(inputFile);
        return 1;
    }

    findWordPositions(inputFile, outputFile, targetWord);

    fclose(inputFile);
    fclose(outputFile);

    printf("Поиск завершен. Результаты записаны в %s\n", outputFilename);

    return 0;
}