#include "headers.h"

int main(void) {
    double res;
    double eps;
    double a, b;
    FILE *in, *out;
    int i;
    int iterations = 0;
    double xn;

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
        if(eps <= 2e-16) {
            fprintf(out, "---------------------\n");
            fprintf(out, "eps less than machine epsilon (double)\n");
            continue;
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

        for(i = 1; i <= 5; i++) {
            iterations = 0;
            //xn = f(b, i) * ddf(b, i) > 0 ? b : a; // можно по-другому брать начальную точку
            xn = (b - a) / 2;
            res = Newton(xn, eps, *f, *df, i, &iterations);

            fprintf(out, "\nTEST %d\n", i);
            if(fabs(b - a) <= eps) fprintf(out, "warning: fabs(b - a) <= eps\n");
            if(res > b || res < a) fprintf(out, "warning: res > b or res < a\n");
            fprintf(out, "answer: %.20lf\n", res);
            fprintf(out, "iterations: %d\n", iterations);
        }
        fprintf(out, "\n");
    }
    fclose(in); fclose(out);
    printf("The results are saved in OUTPUT.txt\n");
    return 0;
}