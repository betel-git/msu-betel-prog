#include <stdio.h>
#include <limits.h>
#include <time.h>

void PrintBinaryTxt(FILE *fo, unsigned long int n);

void PrintBinaryTxt(FILE *fo, unsigned long int n) {
    // Максимальное количество битов в unsigned long int
    const int num_bits = sizeof(n) * CHAR_BIT;
    for (int i = num_bits - 1; i >= 0; i--) {
        fprintf(fo, "%ld", (n >> i) & 1);
        if (i % 8 == 0 && i != 0)
            fprintf(fo, " ");
    }
    fprintf(fo, "\n");
}
 
int main(void) {
    int n;
    unsigned int m = 1;
    FILE *fo;
    time_t t1, t2;
    double seconds;

    fo = fopen("output.txt", "w");
    if (fo == NULL) {
        fprintf (stderr, "Can't open output.txt\n");
        return -1;
    }
   
    printf("n [2...64]: ");
    scanf("%d", &n);
    if (n < 2 || n > 64) {
        fprintf(stderr, "The value outside the given range\n");
        return -1;
    }

    for(int i = 1; i <= n; i++) {
        m = m * 2;
    }

   t1 = clock();
    for (unsigned long int mask = 0; mask < m; ++mask) {
        fprintf(fo, "mask %lu  ", mask);
        PrintBinaryTxt(fo, mask);
        for (int bit = 0; bit < n; ++bit) {
            if (mask & (1 << bit)) {
                fprintf(fo, "%d ", bit + 1);
            }
        }
        fprintf(fo, "\n");
    }
    t2 = clock();
    seconds = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("time: %f\n", seconds);
    return 0;
}

// если не знать, что \Sigma_{k=0}^n C_n^k = 2^n, то можно просто
// взять вместо m (1 << n)