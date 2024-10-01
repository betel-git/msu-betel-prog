#include "greatestsequence.h"

void TestCalculation (const char * fni, const char * fno);

void TestCalculation (const char * fni, const char * fno) {
    int res;
    FILE * f;
    FILE * fo;

    f = fopen(fni, "r");
    if (!f) {
        fprintf(stderr, "Error opening data file\n");
    }

    res = GreatestSequence(f);
    fo = fopen(fno, "w");
    fprintf(fo, "%i", res);

    fclose(f);
    fclose(fo);
}

int main(void) {
    TestCalculation("input1.txt", "output1.txt");
    TestCalculation("input2.txt", "output2.txt");
    return 0;
}