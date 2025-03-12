#include "headers.h"

int main(void) {
    double eps, x;
    double res;
    FILE *inexp, *outexp;
    FILE *insin, *outsin;
    FILE *incos, *outcos;
    FILE *inlog, *outlog;
    
    inexp = fopen("inexp.txt", "r");
    outexp = fopen("outexp.txt", "w");

    while (!feof(inexp)) {
        fscanf(inexp, "%lf", &eps);
        fscanf(inexp, "%lf", &x);
        res = TaylorExp(x, eps);
        fprintf(outexp, "eps = %lg\n",eps);
        fprintf(outexp, "TaylorExp(%lg) = %lg\n", x, res);
        fprintf(outexp, "exp(%lg) = %lg\n", x, exp(x));
        fprintf(outexp, "diff = %lg\n", fabs(res - exp(x)));
        fprintf(outexp, "---------------\n");
    }

    insin = fopen("insin.txt", "r");
    outsin = fopen("outsin.txt", "w");

    while (!feof(insin)) {
        fscanf(insin, "%lf", &eps);
        fscanf(insin, "%lf", &x);
        res = TaylorSin(x, eps);
        fprintf(outsin, "eps = %lg\n",eps);
        fprintf(outsin, "TaylorSin(%lg) = %lg\n", x, res);
        fprintf(outsin, "sin(%lg) = %lg\n", x, sin(x));
        fprintf(outsin, "diff = %lg\n", fabs(res - sin(x)));
        fprintf(outsin, "---------------\n");
    }

    incos = fopen("incos.txt", "r");
    outcos = fopen("outcos.txt", "w");

    while (!feof(incos)) {
        fscanf(incos, "%lf", &eps);
        fscanf(incos, "%lf", &x);
        res = TaylorCos(x, eps);
        fprintf(outcos, "eps = %lg\n",eps);
        fprintf(outcos, "TaylorCos(%lg) = %.10lg\n", x, res);
        fprintf(outcos, "cos(%lg) = %.10lg\n", x, cos(x));
        fprintf(outcos, "diff = %lg\n", fabs(res - cos(x)));
        fprintf(outcos, "---------------\n");
    }

    inlog = fopen("inlog.txt", "r");
    outlog = fopen("outlog.txt", "w");

    while (!feof(inlog)) {
        fscanf(inlog, "%lf", &eps);
        fscanf(inlog, "%lf", &x);
        res = TaylorLog(x, eps);
        fprintf(outlog, "eps = %lg\n",eps);
        fprintf(outlog, "TaylorLog(%lg) = %.10lg\n", x, res);
        fprintf(outlog, "log(%lg) = %.10lg\n", x, log(x));
        fprintf(outlog, "diff = %lg\n", fabs(res - log(x)));
        fprintf(outlog, "---------------\n");
    }

    printf("Success\n");
    return 0;
}