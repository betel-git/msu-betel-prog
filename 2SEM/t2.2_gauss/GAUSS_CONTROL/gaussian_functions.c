#include "headers.h"

// процедура приведения матрицы к ступенчатому виду методом Гаусса
void GaussianElimination (double **a, int rows, int cols, double eps) {
    int i, j, k, lead = 0;
    double temp, div, mult, norm = 0, sum;

    // находит норму матрицы
    for (j = 0; j < cols; j++) {
        sum = 0;
        for (i = 0; i < rows; i++) {
            sum += fabs(a[i][j]);
        }
        if (sum > norm) norm = sum;
    }
    // делит все элементы на норму матрицы
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            a[i][j] /= norm;
        }
    }
    // находит погрешность
    if (rows > cols) eps = eps * rows;
    else eps = eps * cols;
    fprintf(stdout, "new eps = %le\n", eps);

    // непосредственно метод Гаусса
    for (j = 0; j < rows; j++) {
        if( lead >= cols) return;
    
        i = j;
        // ищет ненулевой элемент в столбце, если не находит, то переходит на следующий столбец
        while (fabs(a[i][lead]) < eps) {
            i++;
            if (i == rows) {
                i = j;
                lead++;
                if (lead == cols) return;
            }
        }
        // когда находит ненулевой элемент, меняет j и i строки местами, чтобы сверху была строка с лидером
        if (i != j) {
            for (k = 0; k < cols; k++) {
                temp = a[j][k];
                a[j][k] = a[i][k];
                a[i][k] = temp;
            }
        }
        // делит j строку на значениие лидера
        div = a[j][lead];
        if (fabs(div) > eps) {
            for (k = 0; k < cols; k++) {
                a[j][k] /= div;
            }
        }
        // обнуляет все элементы под лидером
        for (i = j + 1; i < rows; i++) {
            mult = a[i][lead];
            for (k = 0; k < cols; k++) {
                a[i][k] -= a[j][k] * mult;
                //if(a[i][k] < eps) a[i][k] = fabs(a[i][k]); // лишние минусы перед нулём убирает
            }
        }
        lead++;
    }
}

// процедура поиска ранга матрицы
int Rank (double **a, int rows, int cols, double eps) {
    int res = 0, check = 0;
    for (int i = 0; i < rows; i++) {
        check = 0;
        for (int j = 0; j < cols; j++) {
            if (fabs(a[i][j]) > eps) {
                res++;
                check = 1;
                break;
            }
        }
        if (check == 0) break;
    }
    return res;
}

// процедура поиска определителя матрицы
double Determinant (double **a, int rows, int cols, double eps) {
    int i, j, k, lead = 0;
    double temp, div, mult, norm = 0, sum, det = 1;
    
    // если матрица неквадратная
    if (rows != cols) return 0;

    // находит норму матрицы
    for (j = 0; j < cols; j++) {
        sum = 0;
        for (i = 0; i < rows; i++) {
            sum += fabs(a[i][j]);
        }
        if (sum > norm) norm = sum;
    }
    // делит все элементы на норму матрицы
    /*for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            a[i][j] /= norm;
        }
        det *= norm; // умножает определитель на норму
    }*/
    // находит погрешность
    if (rows > cols) eps = eps * rows;
    else eps = eps * cols;
    //fprintf(stdout, "new eps = %le\n", eps);

    // непосредственно метод Гаусса
    for (j = 0; j < rows; j++) {
        if( lead >= cols) return 0;
    
        i = j;
        // ищет ненулевой элемент в столбце, если не находит, то переходит на следующий столбец
        while (fabs(a[i][lead]) < eps) {
            i++;
            if (i == rows) {
                i = j;
                lead++;
                if (lead == cols) return 0;
            }
        }
        // когда находит ненулевой элемент, меняет j и i строки местами, чтобы сверху была строка с лидером
        if (i != j) {
            for (k = 0; k < cols; k++) {
                temp = a[j][k];
                a[j][k] = a[i][k];
                a[i][k] = temp;
            }
            det *= -1; // меняет строки местами
        }
        // делит j строку на значениие лидера
        div = a[j][lead];
        if (fabs(div) > eps) {
            for (k = 0; k < cols; k++) {
                a[j][k] /= div;
            }
            det *= div; // домножает на коэффициент
        }
        // обнуляет все элементы под лидером
        for (i = j + 1; i < rows; i++) {
            mult = a[i][lead];
            for (k = 0; k < cols; k++) {
                a[i][k] -= a[j][k] * mult;
                //a[i][k] = fabs(a[i][k]); // лишние минусы перед нулём убирает
            }
        }
        lead++;
    }
    return det;
}

// обратный ход метода Гаусса (нахождение решения)
void Solver(double **a, double *x, int n) {
    int i, j;
    for (i = n - 1; i >= 0; i--) {
        x[i] = a[i][n];
        for (j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
    }
}

// метод Гаусса + обратный ход = процедура нахождения обратной матрицы
double **GaussianPlusInverse (double **a, int rows, int cols, double eps) {
    double **b;
    int i, j, k, lead = 0;
    double temp, div, mult, norm = 0, sum;

    if (cols != rows) return NULL;

    b = CreateMatrix(rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            b[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // находит норму матрицы
    for (j = 0; j < cols; j++) {
        sum = 0;
        for (i = 0; i < rows; i++) {
            sum += fabs(a[i][j]);
        }
        if (sum > norm) norm = sum;
    }
    // делит все элементы на норму матрицы
    for (j = 0; j < cols; j++) {
        for (i = 0; i < rows; i++) {
            a[i][j] /= norm;
            b[i][j] /= norm;
        }
    }
    // находит погрешность
    if (rows > cols) eps = eps * rows;
    else eps = eps * cols;
    fprintf(stdout, "new eps = %le\n", eps);

    // непосредственно метод Гаусса
    for (j = 0; j < rows; j++) {
        if(lead >= cols) return NULL;
    
        i = j;
        // ищет ненулевой элемент в столбце, если не находит, то переходит на следующий столбец
        while (fabs(a[i][lead]) < eps) {
            i++;
            if (i == rows) {
                i = j;
                lead++;
                if (lead == cols) return NULL;
            }
        }
        // когда находит ненулевой элемент, меняет j и i строки местами, чтобы сверху была строка с лидером
        if (i != j) {
            for (k = 0; k < cols; k++) {
                temp = a[j][k];
                a[j][k] = a[i][k];
                a[i][k] = temp;
                temp = b[j][k];
                b[j][k] = b[i][k];
                b[i][k] = temp;
            }
        }
        // делит j строку на значениие лидера
        div = a[j][lead];
        if (fabs(div) > eps) {
            for (k = 0; k < cols; k++) {
                a[j][k] /= div;
                b[j][k] /= div;
            }
        }
        // обнуляет все элементы под лидером
        for (i = j + 1; i < rows; i++) {
            mult = a[i][lead];
            for (k = 0; k < cols; k++) {
                a[i][k] -= a[j][k] * mult;
                b[i][k] -= b[j][k] * mult;
                //if(a[i][k] < eps) a[i][k] = fabs(a[i][k]); // лишние минусы перед нулём убирает
            }
        }
        lead++;
    }

    // Обратный ход метода Гаусса (приведение к диагональному виду)
    for (k = cols - 1; k >= 0; k--) {
        for (i = k - 1; i >= 0; i--) {
            temp = a[i][k];
            for (j = 0; j < cols; j++) {
                a[i][j] -= a[k][j] * temp;
                b[i][j] -= b[k][j] * temp;
            }
        }
    }
    return b;
}
