// TASK 100
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **FreeMatrix(int **a, int rows);
int **CreateMatrix(int rows, int cols);
void PrintMatrix(int **a, int rows, int cols, FILE *out);

int **CreateMatrix(int rows, int cols) {
    int i;
    int **a;
    a = (int **)malloc(rows * sizeof(int *));
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        a[i] = (int *)malloc(cols * sizeof(int));
        if (a[i] == NULL) {
            FreeMatrix(a, i);
            return NULL;
        }
    }
    return a;
}


int **FreeMatrix(int **a, int rows) {
    int i;
    if (a == NULL) return NULL;
    for (i = 0; i < rows; i++) {
        if (a[i] != NULL) free(a[i]);
    }
    free(a);
    return NULL;
}


void PrintMatrix(int **a, int rows, int cols, FILE *out) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(out, "%d ", a[i][j]);
        }
        fprintf(out, "\n");
    }
}


int main(void) {
    int i, j, k;
    int **a, **c;
    int *cls, *rws;
    int M, N, rows, cols;
    FILE *in, *out;
    int check = 0;

    in = fopen("data.txt", "r");
    if (!in) {
        return -1;
    }

    out = fopen("res.txt", "w");
    if (!out) {
        fclose(in);
        return -1;
    }

    if (fscanf(in, "%d %d %d %d", &M, &N, &rows, &cols) != 4) {
        fprintf(out, "ERROR\n");
        fclose(in); fclose(out);
        return -1;
    }

    if (M < 0 || N < 0 || rows < 0 || cols < 0) {
        fprintf(out, "ERROR\n");
        fclose(in); fclose(out);
        return -1;
    }

    rws = (int *)malloc(rows * sizeof(int));
    if (rws == NULL) {
        fprintf(out, "ERROR\n");
        fclose(in); fclose(out);
        return -1;
    }
    for (i = 0; i < rows; i++) {
        rws[i] = 0;
    }

    cls = (int *)malloc(cols * sizeof(int));
    if (cls == NULL) {
        fprintf(out, "ERROR\n");
        fclose(in); fclose(out); free(rws);
        return -1;
    }
    for (j = 0; j < cols; j++) {
        cls[j] = 0;
    }

    a = CreateMatrix(rows, cols);
    if (a == NULL) {
        fprintf(out, "ERROR\n");
        fclose(in); fclose(out); free(rws); free(cls);
        return -1;
    }

    c = CreateMatrix(rows, cols);
    if (c == NULL) {
        fprintf(out, "ERROR\n");
        fclose(in); fclose(out); free(rws); free(cls); FreeMatrix(a, rows);
        return -1;
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (fscanf(in, "%d", &a[i][j]) != 1) {
                fprintf(out, "ERROR\n");
                fclose(in); fclose(out); free(rws); free(cls); FreeMatrix(a, rows); FreeMatrix(c, rows);
                return -1;
            }
            c[i][j] = a[i][j];
        }
    }
    fclose(in);
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (a[i][j] % M == N) {
                rws[i] = 1;
                cls[j] = 1;
            }
        }
    }

    for (i = 0; i < rows; i++) {
        if (rws[i] == 0) continue;
        for (j = 0; j < cols; j++) {
            if (cls[j] == 0) continue;
            check = 0;
            for (k = 0; k < rows; k++) {
                if (c[k][j] == a[i][j] && k != i && rws[k] == 1) check++;
                if (check >= 2) {
                    a[i][j] = 1;
                    break;
                }
            }
            if (check < 2) a[i][j] = 0;
        }
    }

    fprintf(out, "%d %d %d %d\n", M, N, rows, cols);
    PrintMatrix(a, rows, cols, out);

    fclose(out);
    FreeMatrix(a, rows);
    FreeMatrix(c, rows);
    free(cls);
    free(rws);
    return 0;
}
