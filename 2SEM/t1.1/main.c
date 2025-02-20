#include "headers.h"

int main(void) {
    double res;
    double eps;
    int err = 0;
    double a, b;
    FILE *in, *out;
    int i;
    int iterations = 0;
    double(*f[])(double) = {f0, f1, f2, f3, f4}; // если функций другое количество, то надо это отметить здесь

    if((in = fopen("INPUT.txt", "r"))==NULL) {
        printf("INPUT.txt error\n");
        return -1;
    }

    if((out = fopen("OUTPUT.txt", "w"))==NULL) {
        printf("OUTPUT.txt error\n");
        fclose(in);
        return -1;
    }

    while(!feof(in)){
        if(fscanf(in, "%lf", &eps) != 1){
            fprintf(out, "Not a number value\n");
            printf("The results are saved in OUTPUT.txt\n");
            fclose(in); fclose(out);
            return -2;
        }
        if(fscanf(in, "%lf", &a) != 1){
            fprintf(out, "Not a number value\n");
            printf("The results are saved in OUTPUT.txt\n");
            fclose(in); fclose(out);
            return -2;
        }
        if(fscanf(in, "%lf", &b) != 1){
            fprintf(out, "Not a number value\n");
            printf("The results are saved in OUTPUT.txt\n");
            fclose(in); fclose(out);
            return -2;
        }
        fprintf(out, "---------------------\n");
        fprintf(out, "INPUT: %lg, %lf, %lf\n", eps, a, b);

        for(i = 0; i <= 4; i++) { // если функций другое количество, то надо это отметить здесь
            iterations = 0;
            res = Bisection(a, b, eps, *f[i], &err, &iterations);
            fprintf(out, "\nTEST %d\n", i);
            if(err == 0) fprintf(out, "answer: %.20lf\n", res);
            else if(err == 1) fprintf(out, "warning: fa * fb > 0\n");
            else if(err == 2) {
                fprintf(out, "warning: c <= a || c >= b\n");
                fprintf(out, "answer: %.20lf\n", res);
            }
            else if(err == 3) fprintf(out, "warning: fabs(b - a) <= eps, but f(a) = 0 or f(b) = 0\n");
            else if(err == 4) fprintf(out, "warning: fabs(b - a) <= eps\n");
            fprintf(out, "iterations: %d\n", iterations);
        }
        fprintf(out, "\n");
    }
    fclose(in); fclose(out);
    printf("The results are saved in OUTPUT.txt\n");
    return 0;
}