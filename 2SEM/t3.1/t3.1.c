#include <stdio.h>
#include <stdlib.h>

void cp1251_to_utf8(unsigned char cp1251_char, FILE *out);

void cp1251_to_utf8(unsigned char cp1251_char, FILE *out) {
    int index;
    // если символ ASCII (0-127)
    if (cp1251_char < 0x80) {
        fputc(cp1251_char, out); // просто копируем как есть
    }
    else {
        // для кириллицы (в CP1251 это 0xC0-0xFF)
        const unsigned char utf8_table[64][2] = {
            {0xD0, 0x90}, // А
            {0xD0, 0x91}, // Б
            {0xD0, 0x92}, // В
            {0xD0, 0x93}, // Г
            {0xD0, 0x94}, // Д
            {0xD0, 0x95}, // Е
            {0xD0, 0x96}, // Ж
            {0xD0, 0x97}, // З
            {0xD0, 0x98}, // И
            {0xD0, 0x99}, // Й
            {0xD0, 0x9A}, // К
            {0xD0, 0x9B}, // Л
            {0xD0, 0x9C}, // М
            {0xD0, 0x9D}, // Н
            {0xD0, 0x9E}, // О
            {0xD0, 0x9F}, // П
            {0xD0, 0xA0}, // Р
            {0xD0, 0xA1}, // С
            {0xD0, 0xA2}, // Т
            {0xD0, 0xA3}, // У
            {0xD0, 0xA4}, // Ф
            {0xD0, 0xA5}, // Х
            {0xD0, 0xA6}, // Ц
            {0xD0, 0xA7}, // Ч
            {0xD0, 0xA8}, // Ш
            {0xD0, 0xA9}, // Щ
            {0xD0, 0xAA}, // Ъ
            {0xD0, 0xAB}, // Ы
            {0xD0, 0xAC}, // Ь
            {0xD0, 0xAD}, // Э
            {0xD0, 0xAE}, // Ю
            {0xD0, 0xAF}, // Я
            {0xD0, 0xB0}, // а
            {0xD0, 0xB1}, // б
            {0xD0, 0xB2}, // в
            {0xD0, 0xB3}, // г
            {0xD0, 0xB4}, // д
            {0xD0, 0xB5}, // е
            {0xD0, 0xB6}, // ж
            {0xD0, 0xB7}, // з
            {0xD0, 0xB8}, // и
            {0xD0, 0xB9}, // й
            {0xD0, 0xBA}, // к
            {0xD0, 0xBB}, // л
            {0xD0, 0xBC}, // м
            {0xD0, 0xBD}, // н
            {0xD0, 0xBE}, // о
            {0xD0, 0xBF}, // п
            {0xD1, 0x80}, // р
            {0xD1, 0x81}, // с
            {0xD1, 0x82}, // т
            {0xD1, 0x83}, // у
            {0xD1, 0x84}, // ф
            {0xD1, 0x85}, // х
            {0xD1, 0x86}, // ц
            {0xD1, 0x87}, // ч
            {0xD1, 0x88}, // ш
            {0xD1, 0x89}, // щ
            {0xD1, 0x8A}, // ъ
            {0xD1, 0x8B}, // ы
            {0xD1, 0x8C}, // ь
            {0xD1, 0x8D}, // э
            {0xD1, 0x8E}, // ю
            {0xD1, 0x8F}  // я
        };
        
        // вычисляем индекс в таблице (0xC0 → 0, 0xC1 → 1 и т.д.)
        index = cp1251_char - 0xC0;
        
        if (index >= 0 && index < 64) {
            // записываем два байта UTF-8
            fputc(utf8_table[index][0], out); // первый байт UTF-8
            fputc(utf8_table[index][1], out); // второй байт UTF-8
        }
        else {
            fputc('?', out); // заменяем неизвестные символы
        }
    }
}

int main(void) {
    FILE *in, *out;
    int c;
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

    while ((c = fgetc(in)) != EOF) {
        cp1251_to_utf8((unsigned char)c, out);
    }

    fclose(in);
    fclose(out);
    printf("Success\n");
    return 0;
}
