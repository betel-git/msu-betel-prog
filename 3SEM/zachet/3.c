#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    size_t len_s, len_t;
    int n, m;
    int *res;
    static char s[10005], t[10005];

    // Читаем первую строку s
    if (!fgets(s, sizeof(s), stdin)) return 0;
    // Убираем '\n' если есть
    len_s = strlen(s);
    if (len_s > 0 && s[len_s - 1] == '\n') s[len_s - 1] = '\0';

    // Читаем вторую строку t
    if (!fgets(t, sizeof(t), stdin)) return 0;
    len_t = strlen(t);
    if (len_t > 0 && t[len_t - 1] == '\n') t[len_t - 1] = '\0';

    n = (int)strlen(s);
    m = (int)strlen(t);

    if (m == 0) {
        printf("%d\n", n + 1);
        for (int i = 0; i <= n; ++i) {
            if (i) printf(" ");
            printf("%d", i + 1); // 1-based индексы
        }
        printf("\n");
        return 0;
    }

    if (m > n) {
        printf("0\n");
        return 0;
    }

    res = (int *)malloc((n - m + 1) * sizeof(int));
    if (!res) return 1;

    int cnt = 0;
    for (int i = 0; i <= n - m; ++i) {
        int j;
        for (j = 0; j < m; ++j) {
            char pc = t[j];
            if (pc != '?' && s[i + j] != pc) {
                break; // несовпадение
            }
        }
        if (j == m) {
            res[cnt++] = i + 1; // сохраняем 1-based индекс
        }
    }

    printf("%d\n", cnt);
    for (int k = 0; k < cnt; ++k) {
        if (k) printf(" ");
        printf("%d", res[k]);
    }
    printf("\n");

    free(res);
    return 0;
}