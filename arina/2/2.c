#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n;
    int a;
    char outputFileName[256];
    FILE *out;
    int m = 0;


    printf("Введите имя выходного файла: ");
    scanf("%s", outputFileName);

    // открываем выходной файл
    out = fopen(outputFileName, "w");
    if (!out) {
        printf("Error opening output file\n");
        return -1;
    }


    return 0;
}
