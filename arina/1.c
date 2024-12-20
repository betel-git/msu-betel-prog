#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Len(FILE *f);
void Scan(FILE *f, double *a, int n);
void Func(double *a, int n, double m);
double Mediana(double *a, int n);


int Len(FILE *f) {
    int n = 0;
    double x;
    while(fscanf(f, "%lf", &x) == 1) {
        n++;
    }
    if(!feof(f)){
        return -1;
    }
    rewind(f);
    return n;
}


void Scan(FILE *f, double *a, int n) {
    for (int i = 0; i < n; i++) {
        fscanf(f, "%lf", &a[i]);
    }
}

double Mediana(double *a, int n) {
    double x = 0;
    double res = 0;
    for(int i = 0; i < n; i++) {
        x += a[i];
    }
    res = x / n;
    return res;
}

void Func(double *a, int n, double m) {
    double temp;
    int check = 1;
    while (check != 0) {
        for(int i = 0; i < n - 1; i++) {
            if (fabs(a[i] - m) > fabs(a[i + 1] - m)) {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
        check = 0;
        for (int j = 0; j < n - 1; j++) {
            if (fabs(a[j] - m) > fabs(a[j + 1] - m)) {
                check = 1;
                break;
            }
        }
    }
}


int main(void) {
    FILE *in, *out;
    int n;
    double *a;
    double m;

    in = fopen("input.txt", "r");
    if(in == NULL) {
        printf("-1\n");
        return -1;
    }

    out = fopen("output.txt", "w");
    if(out == NULL) {
        printf("-2\n"); fclose(in);
        return -1;
    }

    n = Len(in);

    if(n == 0 || n == -1) {
        printf("-4\n"); fclose(in); fclose(out);
        return -1;
    }

    a = (double *)malloc(n * sizeof(double));
    if(!a) {
        a = 0;
        printf("-5\n"); fclose(in); fclose(out);
        return -1;
    }

    Scan(in, a, n);
    fclose(in);

    m = Mediana(a, n);
    Func(a, n, m);

    for (int i = 0; i < n; i++) {
		fprintf(out, "%.2f\n", a[i]);
	}

    printf("Success\n");
    fclose(out);
    free(a);
    return 0;
}