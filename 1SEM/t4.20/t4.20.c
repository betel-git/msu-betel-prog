#include <stdio.h>
#include <stdint.h>
#define ICON_SIZE 32

void generate_chessboard(uint32_t k);

void generate_chessboard(uint32_t k) {
    for (uint32_t i = 0; i < ICON_SIZE; i++) {
        char binary_str[32];
        uint32_t row = 0;
        for (uint32_t j = 0; j <= ICON_SIZE; j += k) {
            uint32_t cell_color = (((i / k) + (j / k)) % 2 == 0) ? 0xFFFFFFFF : 0;
            row <<= k;
            row |= (cell_color >> (32 - k));
        }
        for (int i = 31; i >= 0; i--) {
            binary_str[i] = (row >> i) & 1 ? '1' : '0';
        }
        printf("%s\n", binary_str);
    }
}


int main(void) {
    uint32_t k;
    printf("Введите размер клетки k: ");
    scanf("%u", &k);
    if (k > 32 || k < 1) {
        fprintf(stderr, "The value outside the given range\n");
        return -1;
    }

    generate_chessboard(k);
    
    return 0;
}
