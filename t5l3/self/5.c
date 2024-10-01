#include "lastnumber.h"

int main(void) {
    double epsilon, x, res;
    FILE * f;
    FILE * fo;
    //char a;
    //const char * filename;

    //printf("filename: ");
    //scanf("%p", &filename);
    //const char * filename = printf(filename, "input%c.txt", a);

    f = fopen("input1.txt", "r");
    if (!f) {
        fprintf(stderr, "Error opening data file\n");
        return -1;
    }

    printf("epsilon: ");
    scanf("%lf", &epsilon);
    printf("x: ");
    scanf("%lf", &x);

    res = Lastnumber(f, epsilon, x);
    remove("output.txt");
    fo = fopen("output.txt", "w");
    if (fabs(res + 1) <= epsilon) {
        fprintf(fo, "There is no such number\n");
    }
    else {
        fprintf(fo, "Last number`s index is %f\n", res);
    }
    fclose(f);
    return 0;
}