#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROW_COLUMN (1)
#define FIRST_LAST (1)

int read_matrix(const char name[], double **matrix, int *nn, int *mm);
double row_norm(double *a, int n, int m, int i);
double column_norm(double *a, int n, int m, int j);
void selection_sort_rows(double *a, int n, int m, int (*cmp)(double, double));
void selection_sort_columns(double *a, int n, int m, int (*cmp)(double, double));
int compare(double x, double y);
void first_product(double *a, int n, int m, double *res);
void last_product(double *a, int n, int m, double *res);
int write_matrix_and_vector(const char name[], double *a, int n, int m, double *vect);

int main(void){
    double *matrix = 0;
    double *ans = 0;
    int n = 0, m = 0;
    int status = -1;
    const char input_name[] = "input.txt", output_name[] = "output.txt";

    status = read_matrix(input_name, &matrix, &n, &m);
    if (status != 0){
        return -1;
    }

    ans = (double *)malloc(n * sizeof(double));
    if (!ans){
        free(matrix);
        return -1;
    }

    if (ROW_COLUMN == 0){
        if (m > 1){
            selection_sort_rows(matrix, n, m, compare);
        }
    }
    else{
        if (n > 1){
            selection_sort_columns(matrix, n, m, compare);
        }
    }
    if (FIRST_LAST == 0){
        first_product(matrix, n, m, ans);
    }
    else{
        last_product(matrix, n, m, ans);
    }

    status = write_matrix_and_vector(output_name, matrix, n, m, ans);
    if (status != 0){
        free(matrix);
        free(ans);
        return -1;
    }

    free(matrix);
    free(ans);
    return 0;
}


int read_matrix(const char name[], double **matrix, int *nn, int *mm){
    int n, m, size;
    int i;
    double *mtr = 0;
    FILE *input = 0;

    input = fopen(name, "r");
    if (!input){
        return -1;
    }

    if (fscanf(input, "%d", &n) != 1){
        fclose(input);
        return -1;
    }
    if (fscanf(input, "%d", &m) != 1){
        fclose(input);
        return -1;
    }

    size = n * m;
    if (n < 0 || m < 0){
        fclose(input);
        return 0;
    }
    mtr = (double *)(malloc)(size * sizeof(double));
    if (!mtr){
        fclose(input);
        return -1;
    }

    for (i = 0; i < size; i++){
        if (fscanf(input, "%lf", mtr + i) != 1){
            fclose(input);
            free(mtr);
            return -1;
        }
    }

    *nn = n;
    *mm = m;
    *matrix = mtr;
    fclose(input);
    return 0;
}

double row_norm(double *a, int n, int m, int i){
    int j = 0;
    double norm = 0.;
    double curr, prev;
    (void)n;

    prev = a[i * m];
    for (j = 1; j < m; j++){
        curr = a[i * m + j];
        norm += fabs(curr - prev);
        prev = curr;
    }

    return norm;
}

double column_norm(double *a, int n, int m, int j){
    int i = 0;
    double norm = 0.;
    double curr, prev;

    prev = a[j];
    for (i = 1; i < n; i++){
        curr = a[i * m + j];
        if (curr > prev){
            norm += curr - prev;
        }
        prev = curr;
    }

    return norm;
}

int compare(double x, double y){
    return (x <= y) ? -1 : 1;
}

void selection_sort_rows(double *a, int n, int m, int (*cmp)(double, double)){
    int i, j;
    int min_index = 0;
    double curr_norm = 0., best_norm = 0.;
    double temp = 0;

    for (i = 0; i < n; i++){
        min_index = i;
        best_norm = row_norm(a, n, m, i);
        for (j = i + 1; j < n; j++){
            curr_norm = row_norm(a, n, m, j);
            if (cmp(best_norm, curr_norm) > 0){
                min_index = j;
                best_norm = curr_norm;
            }
        }

        for (j = 0; j < m; j++){
            temp = a[i * m + j];
            a[i * m + j] = a[min_index * m + j];
            a[min_index * m + j] = temp;
        }
    }
}

void selection_sort_columns(double *a, int n, int m, int (*cmp)(double, double)){
    int i, j;
    int min_index = 0;
    double curr_norm = 0., best_norm = 0.;
    double temp = 0;

    for (i = 0; i < m; i++){
        min_index = i;
        best_norm = column_norm(a, n, m, i);
        for (j = i + 1; j < m; j++){
            curr_norm = column_norm(a, n, m, j);
            if (cmp(best_norm, curr_norm) > 0){
                min_index = j;
                best_norm = curr_norm;
            }
        }

        for (j = 0; j < n; j++){
            temp = a[j * m + i];
            a[j * m + i] = a[j * m + min_index];
            a[j * m + min_index] = temp;
        }
    }
}

void first_product(double *a, int n, int m, double *res){
    int i, j;
    double sum = 0;

    for (i = 0; i < n; i++){
        sum = 0;
        for (j = 0; j < m; j++){
            sum += a[j] * a[i * m + j];
        }
        res[i] = sum;
    }
}

void last_product(double *a, int n, int m, double *res){
    int i, j;
    double sum = 0;

    for (i = 0; i < n; i++){
        sum = 0;
        for (j = 0; j < m; j++){
            sum += a[(n - 1) * m + j] * a[i * m + j];
        }
        res[i] = sum;
    }
}

int write_matrix_and_vector(const char name[], double *a, int n, int m, double *vect){
    FILE *output;
    int i, j;

    output = fopen(name, "w");
    if (!output){
        return -1;
    }

    fprintf(output, "%d ", n);
    fprintf(output, "%d \n", m);
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++){
            fprintf(output, "%e ", a[i * m + j]);
        }
        fprintf(output, "\n");
    }
    fprintf(output, "\n");
    for (i = 0; i < n; i++){
        fprintf(output, "%e ", vect[i]);
    }

    fclose(output);
    return 0;
}