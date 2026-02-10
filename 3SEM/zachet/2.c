#include <stdio.h>
#include <string.h>

int Sovpadenie(char s_char, char t_char);
int SovpadeniePodstroki(const char* s, const char* t, int start);
void Finder(const char* s, const char* t);


int Sovpadenie(char s_char, char t_char) {
    return (t_char == '?') || (s_char == t_char);
}


int SovpadeniePodstroki(const char* s, const char* t, int start) {
    int t_len = strlen(t);
    
    for (int j = 0; j < t_len; j++) {
        if (!Sovpadenie(s[start + j], t[j])) {
            return 0;
        }
    }
    return 1;
}


void Finder(const char* s, const char* t) {
    int s_len = strlen(s);
    int t_len = strlen(t);
    int found = 0;
    
    if (t_len == 0) {
        printf("Шаблон пустой\n");
        return;
    }
    if (t_len > s_len) {
        printf("Шаблон длиннее строки, вхождений нет\n");
        return;
    }
    for (int i = 0; i <= s_len - t_len; i++) {
        if (SovpadeniePodstroki(s, t, i)) {
            printf("Найдено вхождение на позиции %d\n", i);
            found = 1;
        }
    }
    
    if (!found) {
        printf("Вхождений не найдено\n");
    }
}

int main(void) {
    char s[100], t[100];
    printf("Введите строку s: ");
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = 0;
    
    printf("Введите шаблон t: ");
    fgets(t, sizeof(t), stdin);
    t[strcspn(t, "\n")] = 0;
    
    Finder(s, t);
    
    return 0;
}