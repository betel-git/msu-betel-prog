#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

int total = 0;

pthread_mutex_t  m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  c = PTHREAD_COND_INITIALIZER;

void *Progress(void *)              
{
    int r;
    bool a = true;
    while(a) {
        r = pthread_mutex_lock(&m);
        r = pthread_cond_wait(&c, &m);
        printf("completed %d%%\n", total);
        if (total == 100) { a = false; }
        r = pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *HardWork(void *)
{
    int r;
    for (int i=0; i<=100; i++) {
        r = pthread_mutex_lock(&m);
        total = i;
        printf(" %d",i); fflush(stdout);
        if(i % 10 == 0) { pthread_cond_signal(&c); printf("\nsignal\n"); }
        r = pthread_mutex_unlock(&m);
        usleep(250000);
    }
    pthread_cond_signal(&c); 
    printf("signal\n");
    return NULL;
}

int main()
{
    printf("start\n");
    int r;
    pthread_t p, h;
    r = pthread_create(&p, NULL, Progress, NULL);
    if(r) { fprintf(stderr,"ERROR creating progress thread\n"); exit(0); }
    r = pthread_create(&h, NULL, HardWork, NULL);
    if(r) { fprintf(stderr,"ERROR creating worker thread\n"); exit(0); }

    pthread_detach(p);
    pthread_detach(h);
    printf("stop main\n");
    pthread_exit(0);
}
