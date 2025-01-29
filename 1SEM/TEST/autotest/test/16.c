#include <stdio.h>
#include <stdlib.h>

int Len(FILE *f);
int Len(FILE *f) {
    int n = 0, a;
    while(fscanf(f, "%d", &a) == 1) n++;
    if(!feof(f)) {
        printf("1\n");
        return -1;
    }
    rewind(f);
    return n;
}

void Scan(FILE *f, int *a, int n);
void Scan(FILE *f, int *a, int n) {
    for(int i = 0; i < n; i++) {
        fscanf(f, "%d", &a[i]);
    }
}

int cmp(const void *a, const void *b);
int cmp(const void *a, const void *b) {
    int aa = *(int *)a;
    int bb = *(int *)b;
    if (aa > bb) return 1;
    else if(aa < bb) return -1;
    else return 0;
}

int Func(int *a, int *b, int na, int nb);
int Func(int *a, int *b, int na, int nb) {
    int c = 0;
    for (int i = 0; i < na - 1; i++) {
        c = 0;
        for (int j = 0; j < nb; j++) {
            if (a[i] <= b[j] && a[i + 1] >= b[j]) c++;
        }
        if (c == 0) return -1;
    }
    return 1;
}

int Func2(int *a, int na) {
    int count = 0, res = 0;
    for (int i = 1; i < na; i++) {
        if (a[i] == a[i - 1]) {
            count++;
            for (int j = i; j < na; j++) {
                a[j] = a[j + 1];
            }
        }
    }
    res = na - count;
    return res;
}


int main(void) {
    FILE *ina, *inb, *out;
    int na, nb;
    int *a, *b;
    int check;

    ina = fopen("ina.txt", "r");
    if(ina == NULL) {
        printf("-1\n");
        return -1;
    }
    
    inb = fopen("inb.txt", "r");
    if(inb == NULL) {
        printf("-2\n");
        fclose(ina);
        return -1;
    }

    out = fopen("output.txt", "w");
    if(out == NULL) {
        printf("-3\n"); fclose(ina); fclose(inb);
        return -1;
    }
    
    na = Len(ina);
    nb = Len(inb);
    if(na == 0 || nb == 0 || nb == -1 || na == -1) {
        printf("-4\n"); fclose(ina); fclose(inb); fclose(out);
        return -1;
    }

    a = (int *)malloc(na * sizeof(int));
    if(!a) {
        a = 0;
        printf("-5\n"); fclose(ina); fclose(inb); fclose(out);
        return -1;
    }

    b = (int *)malloc(nb * sizeof(int));
    if(!b) {
        b = 0;
        printf("-6\n"); fclose(ina); fclose(inb); fclose(out); free(a);
        return -1;
    }

    Scan(ina, a, na);
    Scan(inb, b, nb);

    qsort(a, na, sizeof(int), cmp);
    qsort(b, nb, sizeof(int), cmp);

    newlena = Func2(a, na);
    newlenb = Func2(b, nb);
    for (int i = 0; i < newlena) {
        fprintf(out, "%d", a[i]);
    }


    check = Func(a, b, na, nb);
    if (check == -1) fprintf(out, "NO\n");
    else fprintf(out, "YES\n");

    fclose(ina);
    fclose(inb);
    fclose(out);
    free(a);
    free(b);
    printf("Success\n");
    return 0;
}
