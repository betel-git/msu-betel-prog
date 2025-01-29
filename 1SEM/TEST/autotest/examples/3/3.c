#include <stdio.h>
#include <stdlib.h>

int Len(FILE *f);
int Len(FILE *f) {
    int n = 0;
    double x;
    while (fscanf(f, "%lf", &x) == 1) {
        n++;
    }
    if(!feof(f)) {
        return -1;
    }
    rewind(f);
    return n;
}

void Scan(FILE *f, double *arr, int n);
void Scan(FILE *f, double *arr, int n) {
    for (int i = 0; i < n; i++) {
        fscanf(f, "%lf", &arr[i]);
    }
}

int cmp(const void *a, const void *b);
int cmp(const void *a, const void *b) {
    double aa = *(double *)a;
    double bb = *(double *)b;
    if (aa > bb) {
        return 1;
    }
    else if (aa < bb) {
        return -1;
    }
    else return 0;
}

int main() {
    FILE *ina, *inb, *out;
    double *a, *b;
    int na, nb;

    ina = fopen("ina.txt", "r");
    if(ina == NULL) {
        printf("-1\n");
        return -1;
    }
    printf("1\n");

    inb = fopen("inb.txt", "r");
    if(inb == NULL) {
        printf("-2\n");
        fclose(ina);
        return -1;
    }
    printf("2\n");

    out = fopen("output.txt", "w");
    if(out == NULL) {
        printf("-3\n");
        fclose(ina); fclose(inb);
        return -1;
    }
    printf("3\n");

    na = Len(ina);
    nb = Len(inb);
    if(na == 0 || nb == 0 || na == -1 || nb == -1) {
        printf("-4\n");
        fclose(ina); fclose(inb); fclose(out);
        return -1;
    }
    printf("4\n");

    a = (double *)malloc(na * sizeof(double));
    if(!a) {
        a = 0;
        printf("-5\n");
        fclose(ina); fclose(inb); fclose(out);
        return -1;
    }
    b = (double *)malloc(nb * sizeof(double));
    if(!b) {
        b = 0;
        printf("-6\n");
        fclose(ina); fclose(inb); fclose(out); free(a);
        return -1;
    }
    printf("5\n");

    Scan(ina, a, na);
    fclose(ina);
    printf("6\n");
    Scan(inb, b, nb);
    fclose(inb);
    printf("7\n");

    qsort(a, na, sizeof(double), cmp);
    printf("8\n");
    qsort(b, nb, sizeof(double), cmp);
    printf("9\n");

    for (int i = 0; i < na; i++) {
		fprintf(out, "%lf\n", a[i]);
	}
	for (int i = 0; i < nb; i++) {
		fprintf(out, "%g\n", b[i]);
	}

    printf("Success\n");
    free(a);
    free(b);
    fclose(out);
    return 0;
}