#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <pthread.h>
#include <cmath>
#include <utility>

using namespace std;
using namespace std::chrono;

struct MatrixVectorProduct {
    double *mat;
    double *vec;
    double *res;
    int rows, cols, row1, row2;
};

void * matrix_vector_product (void *arg) {
    MatrixVectorProduct *p = static_cast<MatrixVectorProduct*>(arg);
    double sum = 0;
    int i, j;

    for (i = p->row1; i < p->row2; i++) {
        for (j = 0; j < p->cols; j++) {
            sum += p->mat[i * p->cols + j] * p->vec[j];
        }
        p->res[i] = sum;
    }
    return arg;
}

void matrix_vector_product_threads (double *mat, double *vec, double *res, int rows, int cols, int m) {
    MatrixVectorProduct *arg = new MatrixVectorProduct[m];
    pthread_t *th = new pthread_t[m];

    int a = rows / m;
    int b = rows % m;
    int start = 0, end;

    for (int i = 0; i < m; i++) {
        end = start + a + (i < b ? 1 : 0);
        arg[i].mat = mat;
        arg[i].vec = vec;
        arg[i].res = res;
        arg[i].rows = rows;
        arg[i].cols = cols;
        arg[i].row1 = start;
        arg[i].row2 = end;

        pthread_create(&th[i], NULL, matrix_vector_product, &arg[i]);
        start = end;
    }

    for (int i = 0; i < m; i++) {
        pthread_join(th[i], NULL);
    }

    delete[] th;
    delete[] arg;
}

void test_matrix_vector() {
    pair<int, int> sizes[] = {{1000, 1000}, {10000, 10000}, {20000, 20000}};

    for (auto size : sizes) {
        int rows = size.first;
        int cols = size.second;
        cout << "\nРазмер матрицы: " << rows << "x" << cols << endl;
        
        double* mat = new double[rows * cols];
        double* vec = new double[cols];
        double* res = new double[rows];
        int threads[] = {1, 2, 4, 8, 16, 32, 64};
        vector<double> times;
        
        for (int i = 0; i < rows * cols; i++) {
            mat[i] = (double)rand() / RAND_MAX;
        }
        for (int i = 0; i < cols; i++) {
            vec[i] = (double)rand() / RAND_MAX;
        }

        for (int ths : threads) {
            auto t1 = high_resolution_clock::now();
            matrix_vector_product_threads(mat, vec, res, rows, cols, ths);
            auto t2 = high_resolution_clock::now();
            auto dur = duration_cast<microseconds>(t2 - t1);
            times.push_back(dur.count()*1.e-6);
            printf("threads = %d, size = %d, t = %f sec\n", ths, size.first, dur.count()*1.e-6);
        }

        for (int i = 0; i < (int)times.size() - 1; i++) {
            cout << "t" << i << "/t" << i + 1 << ": " << times[i] / times[i + 1] << endl;
        }
        
        delete[] mat;
        delete[] vec;
        delete[] res;
    }
}


int main() {
    srand(time(nullptr));
    test_matrix_vector();
    return 0;
}
