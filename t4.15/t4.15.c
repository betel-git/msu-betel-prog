#include <stdio.h>
#include <limits.h>
#include <time.h>
 
int main(void) {
    long long n;
    long long b = sizeof(n) * CHAR_BIT;
    FILE *fo;
    time_t t1, t2;
    double seconds;
   
    fo = fopen("output.txt", "w");
    if (fo == NULL)
    {
        fprintf (stderr, "Can't open output.txt\n");
        return -1;
    }
   
    printf("n [2.. %lld]: ", b);
    scanf("%lld", &n);
    if (n < 2 || n > b){
        fprintf(stderr, "The value outside the given range\n");
        return -1;
    }

    /*for (unsigned int t = ~(n < b ? ~0 << n:0); t; --t) {
        for (int k = n; k-->0;)
            if (1 << k & t) fprintf(fo," %d",k + 1);
        fprintf(fo,"\n");
    } */

   t1 = clock();
       // Генерируем все подмножества
    for (unsigned int mask = 0; mask < (1ULL << n); ++mask) {
        //printf("%u\n", mask);
        for (int bit = 0; bit < n; ++bit) {
            if (mask & (1ULL << bit)) {
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