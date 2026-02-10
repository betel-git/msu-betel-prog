#include <stdio.h>
#include <string.h>

void Finder(const char* s, const char* t) {
    int s_len = strlen(s);
    int t_len = strlen(t);
    
    printf("Строка s: %s\n", s);
    printf("Шаблон t: %s\n", t);
    printf("Вхождения:\n");
    
    int found = 0;
    
    // Перебираем все возможные начальные позиции в строке s
    for (int i = 0; i <= s_len - t_len; i++) {
        int match = 1;
        
        // Проверяем совпадение для каждой позиции в шаблоне
        for (int j = 0; j < t_len; j++) {
            // Если символ в шаблоне не '?' и не совпадает с символом в строке
            if (t[j] != '?' && t[j] != s[i + j]) {
                match = 0;
                break;
            }
        }
        
        // Если найдено совпадение
        if (match) {
            printf("Индекс %d: ", i);
            
            // Выводим совпадающий фрагмент
            for (int j = 0; j < t_len; j++) {
                printf("%c", s[i + j]);
            }
            printf("\n");
            found = 1;
        }
    }
    
    if (!found) {
        printf("Вхождений не найдено\n");
    }
}

// Альтернативная функция, возвращающая массив индексов
int* find_pattern_indices(const char* s, const char* t, int* count) {
    int s_len = strlen(s);
    int t_len = strlen(t);
    
    // Максимально возможное количество вхождений
    int max_occurrences = s_len - t_len + 1;
    if (max_occurrences <= 0) {
        *count = 0;
        return NULL;
    }
    
    int* indices = malloc(max_occurrences * sizeof(int));
    *count = 0;
    
    for (int i = 0; i <= s_len - t_len; i++) {
        int match = 1;
        
        for (int j = 0; j < t_len; j++) {
            if (t[j] != '?' && t[j] != s[i + j]) {
                match = 0;
                break;
            }
        }
        
        if (match) {
            indices[(*count)++] = i;
        }
    }
    
    return indices;
}

int main() {
    const char* s = "hello world, welcome to programming";
    const char* t = "?o?";
    
    // Использование первой функции
    Finder(s, t);
    
    printf("\n");
    
    // Использование второй функции
    int count;
    int* indices = find_pattern_indices(s, t, &count);
    
    printf("Найдено %d вхождений:\n", count);
    for (int i = 0; i < count; i++) {
        printf("Индекс %d\n", indices[i]);
    }
    
    free(indices);
    
    // Дополнительные примеры
    printf("\n--- Дополнительные примеры ---\n");
    
    const char* s2 = "abcdeffedcba";
    const char* t2 = "??d";
    
    Finder(s2, t2);
    
    return 0;
}