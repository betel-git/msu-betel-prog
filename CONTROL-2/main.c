#include "1.h"

int main(void) {
    // инициализация переменных обязательно в самом начале
    FILE *ina, *inb, *output;
    int na = 0, nb = 0, nc = 0;
    int *a, *b, *c;
    int ia = 0, ib = 0, ic = 1;
    int p;

    // открываем ina.txt
    ina = fopen("ina.txt", "r");
    if(!ina) {
        printf("Error ina.txt\n");
        perror("aaa");
        return -1;
    }

    // открываем inb.txt
    inb = fopen("inb.txt", "r");
    if(!inb) {
        printf("Error inb.txt\n");
        fclose(ina); // закрываем ina
        return -1;
    }

    // открываем output.txt
    output = fopen("output.txt", "w");
    if(!output) {
        printf("Error output.txt\n");
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        return -1;
    }

    // измеряем длину ina
    na = NArray(ina);
    if(na == 0) {
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        return -1;
    }

    // измеряем длину inb
    nb = NArray(inb);
    if(nb == 0) {
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        return -1;
    }

    // читаем a массив
    a = ReadArray(ina, na);
    if(!a) {
        fclose(ina); // закрываем ina
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        return -1;
    }
    // закрываем ina, больше не нужен
    fclose(ina);

    // читаем b массив
    b = ReadArray(inb, nb);
    if(!b) {
        fclose(inb); // закрываем inb
        fclose(output); // закрываем output
        free(a); // освобождаем выделенную под a память
        return -1;
    }
    // закрываем inb, больше не нужен
    fclose(inb);

    // библиотечная сортировка по фукнции сравнения
    qsort(a, na, sizeof(int), cmp);
    qsort(b, nb, sizeof(int), cmp);

    // функциональная часть
    nc = na + nb;
    c = (int *)malloc(nc * sizeof(int));
    if(!c) {
        printf("Malloc Error\n");
        c = 0;
        fclose(output);
        free(a);
        free(b);
        return -1;
    }

    while(ic < nc) {
        p = Min(a[ia], b[ib]);
        if (p != c[ic - 1]) {
            c[ic] = p;
            ic++;
        }
        if (p == a[ia]) ia++;
        else if (p == b[ib]) ib++;
    }








/* 
    for (int i = 0; i < na; i++) {
        for (int j = 0; j < nb; j++) {
            if (a[i] == b[j]) {
                count++;
            }
        }
    }
    
    nc = na + nb - count;
    
    if (nc == 0) {
        fprintf(output, "%d\n", a[0]);
        fclose(output);
        free(a);
        free(b);
        return 0;
    }
    
    c = (int *)malloc(nc * sizeof(int));
    if(!c) {
        printf("Malloc Error\n");
        c = 0;
        return -1;
    }
    
    printf("\n");
    for (ia = 0; ia < na; ia++) {
        printf("%d\n", a[ia]);
    }
    for (ib = 0; ib < nb; ib++) {
        printf("%d\n", b[ib]);
    }
    ia = 0; ib = 0;
    
    
    printf("nc %d\n", nc);
    while (ic < nc) {
        if (ia < na && ib < nb) {
            if (a[ia] < b[ib]) {
                c[ic] = a[ia];
                ic++;
                ia++;
                //printf("c1 %d\n", ic - 1);
                //printf("c %d\n", c[ic - 1]);
                continue;
            }
            else if (b[ib] < a[ia]) {
                c[ic] = b[ib];
                ic++;
                ib++;
                //printf("c2 %d\n", ic - 1);
                //printf("c %d\n", c[ic - 1]);
                continue;
            }
            else if( a[ia] == b[ib]) {
                c[ic] = a[ia];
                ic++;
                ib++;
                ia++;
                //printf("c3 %d\n", ic - 1);
                //printf("c %d\n", c[ic - 1]);
                continue;
            }
        }
        else if (ia == na) {
            while (ib < nb) {
                c[ic] = b[ib];
                ib++;
                ic++;
            }
        }
        else if (ib == nb) {
            while (ia < na) {
                c[ic] = a[ia];
                ia++;
                ic++;
            }
        }
    }
    
    
    count = 0;
    for (i = 1; i < nc; i++) {
        if (c[i - 1] == c[i]) {
            count++;
        }
    }
    nd = nc - count;
    printf("nd %d\n", nd);
    d = (int *)malloc(nd * sizeof(int));
    if(!d) {
        printf("Malloc Error\n");
        d = 0;
        return -1;
    }
    while (id < nd) {
        if (c[ic - 1] == c[ic]) {
            ic++;
            continue;
        }
        else {
            d[id] = c[ic];
            ic++;
            id++;
        }
    }
    
     */
    for (int i = 0; i < nc; i++) {
        fprintf(output, "%d\n", c[i]);
    }

    // закрываем все файлы, освобождаем память
    fclose(output);
    free(a);
    free(b);
    free(c);
    printf("Success\n");
    return 0;
}
