#include <cstdio>
#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include "matrvectinit.h"

double GetTimeOfDay()
{
    timeval buf;
    gettimeofday(&buf, 0);
    double s = buf.tv_sec;
    s += double(buf.tv_usec)/1000000;
    return s;
}

struct Data {
    double *matr;            // matrix
    double *vect;            // vector
    double *rvect;           // result vector
    unsigned nrows, ncols;   // matrix sizes
    unsigned ibeg, iend;     // start and end row indices
};

void *MatrVect_1(void *arg)
{
    // parallelize over matrix rows
    // get start time
    double t1 = GetTimeOfDay();
                      
    // extract parameters                                            
    Data * param = static_cast<Data*>(arg);
    double *matr = param->matr;
    double *vect = param->vect;
    double *rvect = param->rvect;
    unsigned nrows = param->nrows, ncols = param->ncols;
    unsigned ibeg = param->ibeg, iend = param->iend;
  
    // multiplication
    for (unsigned i = ibeg; i < iend; i++) {
        rvect[i] = 0;
        for (unsigned j = 0; j < ncols; j++) {
            rvect[i] += matr[i*ncols + j]*vect[j];
        }
    }
    // get end time
    double t2 = GetTimeOfDay();
    printf("time %f\n", t2 - t1);
    return nullptr;
}
    
int main()
{
    double t1, t2;
    unsigned n = 20000;     // size of square matrix

    double *matr = InitMatrix(n, n);
    double *vect = InitVector(n, true);                        
    double *rvect = InitVector(n);
    double *rvect2 = InitVector(n);
    Data single = {matr, vect, rvect, n, n, 0, n};

    printf("one thread:\n");
    pthread_t pth;
    auto r = pthread_create(&pth, NULL, MatrVect_1, &single);
    if(r) { fprintf(stderr,"ERROR creating thread single\n"); exit(0); }
    pthread_join(pth, NULL);

    int npth = 4;     // number of threads
    printf("%d threads:\n", npth);
    Data *many = (Data*)malloc(npth*sizeof(Data)); 
    pthread_t *pthmany = (pthread_t*)malloc(npth*sizeof(pthread_t)); 
    t1 = GetTimeOfDay();
    for (int i = 0; i<npth; i++) {
        many[i].matr = matr;
        many[i].vect = vect;
        many[i].rvect = rvect2;
        many[i].nrows = n;
        many[i].ncols = n;
        many[i].ibeg = (n / npth)*i;
        many[i].iend = (n / npth)*(i+1);
        r = pthread_create(&pthmany[i], NULL, MatrVect_1, &many[i]);
        if(r) { fprintf(stderr,"ERROR creating thread many %d\n", i); exit(0); }
    }
    // waiting for all threads to finish
    for (int i = 0; i<npth; i++) {
        pthread_join(pthmany[i], NULL);
    }
    t2 = GetTimeOfDay();
    printf("total time %f\n", t2 - t1);

    free(matr);
    free(vect);
    free(rvect);
    free(rvect2);
    free(many);
    free(pthmany);
    return 0;
}
