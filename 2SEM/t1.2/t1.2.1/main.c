#include "headers.h"

int main(void) {
    double a, b, eps, result, check;
    int n = 0;
    int err = 0;
    double(*f[])(double) = {f1};
    double(*F[])(double) = {F1};
    FILE *in, *out;

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
        
        for(int i = 0; i < 1; i++) {
            result = Integral(a, b, eps, &n, &err, *f[i]);
            check = Verification(a, b, *F[i]);
            fprintf(out, "\nFunction %d\n", i + 1);
            if (err == -1) fprintf(out, "warning: iterations > 25\n");
            fprintf(out, "answer: %.20lf\n", result);
            if (check >= 0 && check <= 0) fprintf(out, "function has no F or F(b) - F(a) == 0\n");
            else fprintf(out, "right answer: %.15lf\n", check);
            fprintf(out, "delta: %.20lf\n", result - check);
            fprintf(out, "n: %d\n", n);
            //printf("check\n");
        }
        fprintf(out, "\n");
        
    }
    fclose(in); fclose(out);
    printf("The results are saved in OUTPUT.txt\n");
    return 0;
}