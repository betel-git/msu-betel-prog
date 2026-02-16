#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <pthread.h>
#include <cmath>
#include <tuple>

using namespace std;
using namespace std::chrono;

struct MatrixProduct {
    double *A;
    double *B;
    double *C;
    int m, n, k;
    int row1, row2;
};

void * matrix_product (void *arg) {
    MatrixProduct *p = static_cast<MatrixProduct*>(arg);

    int i, j, l;
    double sum = 0;
    for (i = p->row1; i < p->row2; i++) {
        for (j = 0; j < p->k; j++) {
            sum = 0;
            for (l = 0; l < p->n; l++) {
                sum += p->A[i * p->n + l] * p->B[l * p->k + j];
            }
            p->C[i * p->k + j] = sum;
        }
    }
    return arg;
}

void matrix_product_threads (double *A, double *B, double *C, int m, int n, int k, int ths) {
    MatrixProduct *arg = new MatrixProduct[ths];
    pthread_t *th = new pthread_t[ths];

    int a = m / ths;
    int b = m % ths;
    int start = 0, end;

    for (int i = 0; i < ths; i++) {
        end = start + a + (i < b ? 1 : 0);
        arg[i].A = A;
        arg[i].B = B;
        arg[i].C = C;
        arg[i].m = m;
        arg[i].n = n;
        arg[i].k = k;
        arg[i].row1 = start;
        arg[i].row2 = end;

        pthread_create(&th[i], NULL, matrix_product, &arg[i]);
        start = end;
    }

    for (int i = 0; i < ths; i++) {
        pthread_join(th[i], NULL);
    }

    delete[] th;
    delete[] arg;
}

void test_matrix_product() {
    tuple<int, int, int> sizes[] = {{100, 100, 100}, {200, 200, 200}, {300, 300, 300}};

    for (auto size : sizes) {
        int m = get<0>(size);
        int n = get<1>(size);
        int k = get<2>(size);
        cout << "\nРазмер матриц: A(" << m << "x" << n << ") * B(" << n << "x" << k << ")" << endl;
        
        double* A = new double[m * n];
        double* B = new double[n * k];
        double* C = new double[m * k];
        int threads[] = {1, 2, 4, 8, 16, 32, 64};
        vector<double> times;
        
        for (int i = 0; i < m * n; i++) {
            A[i] = (double)rand() / RAND_MAX;
        }
        for (int i = 0; i < n * k; i++) {
            B[i] = (double)rand() / RAND_MAX;
        }
        
        for (int ths : threads) {
            auto t1 = high_resolution_clock::now();
            matrix_product_threads(A, B, C, m, n, k, ths);
            auto t2 = high_resolution_clock::now();
            auto dur = duration_cast<microseconds>(t2 - t1);
            times.push_back(dur.count()*1.e-6);
            printf("threads = %d, size = %d, t = %f sec\n", ths, get<0>(size), dur.count()*1.e-6);
        }

        for (int i = 0; i < (int)times.size() - 1; i++) {
            cout << "t" << i << "/t" << i + 1 << ": " << times[i] / times[i + 1] << endl;
        }
        
        delete[] A;
        delete[] B;
        delete[] C;
    }
}

int main() {
    srand(time(nullptr));
    test_matrix_product();
    return 0;
}
