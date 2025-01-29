#include <stdio.h>
#include <stdlib.h>

int Narray(FILE *f);
int Narray(FILE *f) {
    int n = 0;
    int x;
    while(fscanf(f, "%d", &x) == 1) {
        n++;
    }
    if (!feof(f)) {
        return -1;
    }
    rewind(f);
    return n;
}

int* Array(FILE *f, int n);
int* Array(FILE *f, int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        printf("Malloc Error\n");
        arr = 0;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &arr[i]);
    }
    return arr;
}

int cmp(const void *a, const void *b);
int cmp(const void *a, const void *b) {
    int aa = *(int *)a;
    int bb = *(int *)b;
    if (aa > bb) {
        return 1;
    }
    else if (aa < bb) {
        return -1;
    }
    else return 0;
}




int main(void) {
    FILE *ina, *inb, *output;
    int *a, *b;
    int na, nb;

    ina = fopen("ina.txt", "r");
    if (ina == NULL) {
        printf("Error ina.txt\n");
        return -1;
    }

    inb = fopen("inb.txt", "r");
    if (!inb) {
        printf("Error inb.txt\n");
        fclose(ina);
        return -1;
    }

    printf("Both files are open\n");

    output = fopen("output.txt", "w");
    if (!output) {
        printf("Error output.txt\n");
        fclose(ina);
        fclose(inb);
        return -1;
    }

    printf("Output file is open\n");

    na = Narray(ina);
    if (na == -1) {
        printf("na == -1");
        fclose(ina);
        fclose(inb);
        fclose(output);
        return -1;
    }

    printf("na != -1\n");
    
    nb = Narray(inb);
    if (nb == -1) {
        printf("nb == -1");
        fclose(ina);
        fclose(inb);
        fclose(output);
        return -1;
    }

    printf("nb != -1\n");

    a = Array(ina, na);
    if (!a) {
        fclose(ina);
        fclose(inb);
        fclose(output);
    }
    fclose(ina);

    b = Array(inb, nb);
    if (!b) {
        fclose(inb);
        fclose(output);
    }
    fclose(inb);

    qsort(a, na, sizeof(int), cmp);
    qsort(b, nb, sizeof(int), cmp);

    for (int i = 0; i < na; i++) {
        fprintf(output, "%d\n", a[i]);
    }
    for (int i = 0; i < nb; i++) {
        fprintf(output, "%d\n", b[i]);
    }
    fclose(output);
    free(a);
    free(b);
    return 0;
}