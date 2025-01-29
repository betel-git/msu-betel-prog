#include <stdio.h>
#include <stdlib.h>

int Len(FILE *f);
int Len(FILE *f) {
    int n = 0;
    int x;
    while(fscanf(f, "%d", &x) == 1) {
        n++;
    }
    if(!feof(f)){
        return -1;
    }
    rewind(f);
    return n;
}

void Scan(FILE *f, int *a, int n);
void Scan(FILE *f, int *a, int n) {
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &a[i]);
    }
}

int cmp(const void *a, const void *b);
int cmp(const void *a, const void *b) {
    int aa = *(int *)a;
    int bb = *(int *)b;
    if(aa > bb) {
        return 1;
    }
    else if(aa < bb) {
        return -1;
    }
    else return 0;
}

int main(void) {
    FILE *ina, *inb, *out;
    int na, nb;
    int *a, *b;

    ina = fopen("ina.txt", "r");
    if(ina == NULL) {
        printf("-1\n");
        return -1;
    }
    printf("1\n");

    inb = fopen("inb.txt", "r");
    if(inb == NULL) {
        printf("-2\n"); fclose(ina);
        return -1;
    }
    printf("2\n");

    out = fopen("output.txt", "w");
    if(out == NULL) {
        printf("-3\n"); fclose(ina); fclose(inb);
        return -1;
    }
    printf("3\n");

    na = Len(ina);
    printf("4\n");
    nb = Len(inb);
    printf("5\n");

    if(na == 0 || nb == 0 || na == -1 || nb == -1) {
        printf("-4\n"); fclose(ina); fclose(inb);
        return -1;
    }

    a = (int *)malloc(na * sizeof(int));
    if(!a) {
        a = 0;
        printf("-5\n"); fclose(ina); fclose(inb); fclose(out);
        return -1;
    }
    printf("6\n");
    b = (int *)malloc(nb * sizeof(int));
    if(!b) {
        b = 0;
        printf("-6\n"); fclose(ina); fclose(inb); fclose(out); free(a);
        return -1;
    }
    printf("7\n");

    Scan(ina, a, na);
    fclose(ina);
    printf("8\n");
    Scan(inb, b, nb);
    fclose(inb);
    printf("9\n");

    qsort(a, na, sizeof(int), cmp);
    qsort(b, nb, sizeof(int), cmp);

    printf("Success\n");
    fclose(out);
    free(a);
    free(b);
}