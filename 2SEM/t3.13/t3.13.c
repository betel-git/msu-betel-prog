#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_DEFINES 100
#define MAX_CURRENT_DEFINES 32

void TrimLeadingSpaces(char *str);
void AddToSet(char set[][MAX_LINE_LENGTH], int *size, const char *name);
void RemoveLastFromSet(char set[][MAX_LINE_LENGTH], int *size);
int IsInSet(char set[][MAX_LINE_LENGTH], int size, const char *name);
int ShouldPrint(void);
void PreprocessorFunction(FILE *input, FILE *output);


// Множество определенных имен
char Defset[MAX_DEFINES][MAX_LINE_LENGTH];
int Defset_size = 0;

// Множества для условий блоков
char DefsetYES[MAX_CURRENT_DEFINES][MAX_LINE_LENGTH];
char DefsetNO[MAX_CURRENT_DEFINES][MAX_LINE_LENGTH];
int DefsetYES_size = 0;
int DefsetNO_size = 0;

// Функция, которая удаляет начальные пробелы в строке
void TrimLeadingSpaces(char *str) {
    char *first_non_space;
    if (str == NULL) return;
    
    // находим первый непробельный символ
    first_non_space = str;
    while (isspace((unsigned char)*first_non_space)) {
        first_non_space++;
    }
    
    // если есть пробелы в начале, сдвигаем строку
    if (first_non_space != str) {
        size_t len = strlen(first_non_space);
        memmove(str, first_non_space, len + 1);
    }
}


// Добавляет имя в множество
void AddToSet(char set[][MAX_LINE_LENGTH], int *size, const char *name) {
    if (*size >= MAX_DEFINES) {
        fprintf(stderr, "Ошибка из AddToSet: слишком много определений\n");
        exit(1);
    }
    strncpy(set[*size], name, MAX_LINE_LENGTH - 1);
    set[*size][MAX_LINE_LENGTH - 1] = '\0';
    (*size)++;
}


// Удаляет последнее имя из множества
void RemoveLastFromSet(char set[][MAX_LINE_LENGTH], int *size) {
    if (*size <= 0) {
        fprintf(stderr, "Ошибка из RemoveLastFromSet: пустое множество\n");
        exit(1);
    }
    memset(set[*size - 1], 0, MAX_LINE_LENGTH);
    (*size)--;
}


// Проверяет, содержится ли имя в множестве
int IsInSet(char set[][MAX_LINE_LENGTH], int size, const char *name) {
    for (int i = 0; i < size; i++) {
        if (strcmp(set[i], name) == 0) {
            return 1;
        }
    }
    return 0;
}


// Проверяет, нужно ли печатать текущую строку
int ShouldPrint(void) {
    // проверяем все имена в DefsetYES
    for (int i = 0; i < DefsetYES_size; i++) {
        if (!IsInSet(Defset, Defset_size, DefsetYES[i])) {
            return 0;
        }
    }
    // проверяем все имена в DefsetNO
    for (int i = 0; i < DefsetNO_size; i++) {
        if (IsInSet(Defset, Defset_size, DefsetNO[i])) {
            return 0;
        }
    }
    return 1;
}


// Основная функция
void PreprocessorFunction(FILE *input, FILE *output) {
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, MAX_LINE_LENGTH, input)) {
        // проверка на длину строки
        if (strchr(line, '\n') == 0) {
            fprintf(stderr, "Ошибка из PreprocessorFunction: введенная строка слишком длинная (максимум %d символов)\n", MAX_LINE_LENGTH - 1);
            exit(1);
        }
        else {
            line[strcspn(line, "\n")] = '\0'; // удаляем завершающий символ новой строки
            TrimLeadingSpaces(line); // удаляем лишние пробелы
        }
        // обработка директив
        if (strncmp(line, "#ifdef ", 7) == 0) {
            char name[MAX_LINE_LENGTH];
            sscanf(line + 7, "%s", name);
            AddToSet(DefsetYES, &DefsetYES_size, name);
        }
        else if (strncmp(line, "#ifndef ", 8) == 0) {
            char name[MAX_LINE_LENGTH];
            sscanf(line + 8, "%s", name);
            AddToSet(DefsetNO, &DefsetNO_size, name);
        }
        else if (strcmp(line, "#else") == 0) {
            if (DefsetYES_size > 0) {
                // переносим последнее имя из DefsetYES в DefsetNO
                char last_name[MAX_LINE_LENGTH];
                strcpy(last_name, DefsetYES[DefsetYES_size - 1]);
                RemoveLastFromSet(DefsetYES, &DefsetYES_size);
                AddToSet(DefsetNO, &DefsetNO_size, last_name);
            }
            else if (DefsetNO_size > 0) {
                // переносим последнее имя из DefsetNO в DefsetYES
                char last_name[MAX_LINE_LENGTH];
                strcpy(last_name, DefsetNO[DefsetNO_size - 1]);
                RemoveLastFromSet(DefsetNO, &DefsetNO_size);
                AddToSet(DefsetYES, &DefsetYES_size, last_name);
            }
        }
        else if (strcmp(line, "#endif") == 0) {
            if (DefsetYES_size > 0) {
                RemoveLastFromSet(DefsetYES, &DefsetYES_size);
            }
            else if (DefsetNO_size > 0) {
                RemoveLastFromSet(DefsetNO, &DefsetNO_size);
            }
        }
        else if (strncmp(line, "#define ", 8) == 0) {
            char name[MAX_LINE_LENGTH];
            sscanf(line + 8, "%s", name);
            AddToSet(Defset, &Defset_size, name);
        }
        else if (strncmp(line, "#undef ", 7) == 0) {
            char name[MAX_LINE_LENGTH];
            sscanf(line + 7, "%s", name);
            for (int i = 0; i < Defset_size; i++) {
                if (strcmp(Defset[i], name) == 0) {
                    // удаляем имя из Defset
                    for (int j = i; j < Defset_size - 1; j++) {
                        strcpy(Defset[j], Defset[j + 1]);
                    }
                    Defset_size--;
                    break;
                }
            }
        }
        else {
            // обычная строка — печатаем, если условия выполняются
            if (ShouldPrint()) {
                fprintf(output, "%s\n", line);
            }
        }
    }
}


int main(void) {
    FILE *in, *out;
    in = fopen("input.c", "r");
    if (!in) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    out = fopen("output.c", "w");
    if (!out) {
        perror("Ошибка открытия выходного файла");
        fclose(in);
        return -1;
    }

    PreprocessorFunction(in, out);
    fclose(in);
    fclose(out);
    printf("Success\n");
    return 0;
}
