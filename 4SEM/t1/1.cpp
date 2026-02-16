#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <pthread.h>
#include <cmath>

using namespace std;
using namespace std::chrono;


struct ScalarProduct {
    double *v1;
    double *v2;
    int start;
    int end;
    double res;
};


void * scalar_product (void *arg) {
    ScalarProduct *p = static_cast<ScalarProduct*>(arg);
    p->res = 0;
    
    for (int i = p->start; i < p->end; i++) {
        p->res += p->v1[i] * p->v2[i];
    }

    return arg;
}

double scalar_product_threads (double *v1, double *v2, int n, int m) {
    ScalarProduct *arg = new ScalarProduct[m];
    pthread_t *th = new pthread_t[m];

    int a = n / m;
    int b = n % m;
    int start = 0;
    int r;

    for (int i = 0; i < m; i++) {
        int end = start + a + (i < b ? 1 : 0);
        arg[i].v1 = v1;
        arg[i].v2 = v2;
        arg[i].start = start;
        arg[i].end = end;
        start = end;
        r = pthread_create(&th[i], NULL, scalar_product, &arg[i]);
        if(r) { fprintf(stderr,"ERROR creating thread %d\n", i); exit(0); }
    }

    double s = 0;
    for (int i = 0; i < m; i++) {
        r = pthread_join(th[i],NULL);
        if(r) { fprintf(stderr,"ERROR joining thread %d\n", i); exit(0); }
        s += arg[i].res;
    }

    return s;
}

void test_scalar_product() {
    for (int size : {100000, 1000000, 10000000}) {
        cout << "\nРазмер векторов: " << size << endl;
        
        double* v1 = new double[size];
        double* v2 = new double[size];
        int threads[] = {1, 2, 4, 8, 16, 32, 64};
        vector<double> times;
        
        
        for (int i = 0; i < size; i++) {
            v1[i] = (double)rand() / RAND_MAX;
            v2[i] = (double)rand() / RAND_MAX;
        }

        for (int ths : threads) {
            auto t1 = high_resolution_clock::now();
            double res = scalar_product_threads(v1, v2, size, ths);
            auto t2 = high_resolution_clock::now();
            auto dur = duration_cast<microseconds>(t2 - t1);
            times.push_back(dur.count()*1.e-6);
            printf("res = %lf, threads = %d, size = %d, t = %f sec\n", res, ths, size, dur.count()*1.e-6);
            
            //cout << ths << " потока(ов): " << ", результат: " << res << endl;
        }
        
        for (int i = 0; i < (int)times.size() - 1; i++) {
            cout << "t" << i << "/t" << i + 1 << ": " << times[i] / times[i + 1] << endl;
        }
        
        delete[] v1;
        delete[] v2;
    }
}


int main() {
    srand(time(nullptr));
    test_scalar_product();
    return 0;
}
