#include <stdio.h>
#include <stdlib.h>

void GeneralFunc(FILE *in, FILE *out);

void GeneralFunc(FILE *in, FILE *out) {
    int current_char, previous_char = EOF;

    while ((current_char = fgetc(in)) != EOF) {
        if (current_char != previous_char) {
            fputc(current_char, out);
            previous_char = current_char;
        }
    }
}

int main(void) {
    FILE *in, *out;
    in = fopen("input.txt", "r");
    if (!in) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    out = fopen("output.txt", "w");
    if (!out) {
        perror("Ошибка открытия выходного файла");
        fclose(in);
        return -1;
    }

    GeneralFunc(in, out);

    fclose(in);
    fclose(out);
    printf("Success\n");
    return 0;
}
