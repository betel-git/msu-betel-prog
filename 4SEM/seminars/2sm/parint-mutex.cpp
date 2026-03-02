#include <cstdio>
#include <unistd.h>
#include <cmath>
#include <pthread.h>
#include <chrono>

using namespace std::chrono;

pthread_mutex_t mut_int = PTHREAD_MUTEX_INITIALIZER;

// интегрирование примитивным методом трапеций

struct Data {
    double a, b;             // отрезок интегрирования
    unsigned n;              // количество разбиений
    double (*fun)(double);   // подинтегральная функция
    double *result;          // накопитель значения интеграла
};

void * Integral (void * arg)
{
    auto t1 = high_resolution_clock::now();
    Data *p = static_cast<Data*>(arg);
    double a = p->a, b = p->b;
    unsigned n = p->n;
    int res;

    // простейший метод трапеций
    double h = (b - a)/n;
    double s = 0.5*(p->fun(a) + p->fun(b));
    for (unsigned i = 1; i < n; i++) {
        s += p->fun(a + i*h);
    }  
    res = pthread_mutex_lock(&mut_int);
    if(res) { fprintf(stderr,"ERROR mutex lock\n"); exit(0); }
    *(p->result) += s * h;
    res = pthread_mutex_unlock(&mut_int);
    if(res) { fprintf(stderr,"ERROR mutex unlock\n"); exit(0); }

    // подсчет времени и печать параметров
    auto t2 = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(t2 - t1);
    printf("a=%.5f b=%.5f n=%u t=%f sec\n", a, b, n, dur.count()*1.e-6);
    return arg;
}

double PthIntegral (double a, double b, unsigned n, double (*fun)(double), int n_threads)
{
    auto t1 = high_resolution_clock::now();
    Data *arg = new Data[n_threads];
    pthread_t *th = new pthread_t[n_threads];
    int res;
    double s = 0;
    double H = (b - a)/n_threads;
    for (unsigned i = 0; i < n_threads; i++) {
        arg[i].a = a + i*H;
        arg[i].b = a + (i+1)*H;
        arg[i].n = n / n_threads;
        arg[i].fun = fun;
        arg[i].result = &s;
        res = pthread_create(&th[i], NULL, Integral, &arg[i]);
        if(res) { fprintf(stderr,"ERROR creating thread %d\n", i); exit(0); }
    }

    for(unsigned i = 0; i < n_threads; i++) {
        res = pthread_join(th[i],NULL);
        if(res) { fprintf(stderr,"ERROR joining thread %d\n", i); exit(0); }
    }

    auto t2 = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(t2 - t1);
    printf("\na=%.5f b=%.5f n=%u t=%f sec\n", a, b, n, dur.count()*1.e-6);
    delete [] th;
    delete [] arg;
    return s;                                
}

int main()
{
    double result;

    printf("without pthread:\n");
    result = PthIntegral(0, 1, 1000000000, exp, 1);
    printf("result = %.16f\n",result);

    printf("with pthreads\n");
    result = PthIntegral(0, 1, 1000000000, exp, 6);
    printf("result = %.16f\n",result);

    int ret = pthread_mutex_destroy(&mut_int);
    if(ret) { fprintf(stderr,"ERROR mutex destroy\n"); exit(0); }

    return 0;
}

