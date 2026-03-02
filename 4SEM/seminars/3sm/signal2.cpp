#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

int total = 0;

pthread_mutex_t  m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  c1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t  c2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t  c3 = PTHREAD_COND_INITIALIZER;

void *Progress(void *arg)              
{
    pthread_cond_t *pc = *(pthread_cond_t**)arg;
    bool a = true;
    while(a) {
        pthread_mutex_lock(&m);
        pthread_cond_wait(pc, &m);
        printf("completed %d%%\n", total);
        if (total == 100) { a = false; }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *HardWork(void *arg)
{
    for (int i=0; i<=100; i++) {
        pthread_mutex_lock(&m);
        total = i;
        printf(" %d", i); fflush(stdout);
        if(i % 10 == 0) { pthread_cond_signal(&c1); printf("\nsignal_1\n"); }
        if(i % 20 == 0) { pthread_cond_signal(&c2); printf("signal_2\n"); }
        if(i % 40 == 0) { pthread_cond_signal(&c3); printf("signal_4\n"); }
        pthread_mutex_unlock(&m);
        usleep(250000);
    }
    pthread_cond_signal(&c1); 
    pthread_cond_signal(&c2); 
    pthread_cond_signal(&c3); 
    printf("signal all\n");
    return NULL;
}

int main()
{
    printf("start\n");
    int r;
    pthread_t p1, p2, p3, h;
    pthread_cond_t * pc1 = &c1;
    pthread_cond_t * pc2 = &c2;
    pthread_cond_t * pc3 = &c3;

    r = pthread_create(&p1, NULL, Progress, &pc1);
    if(r) { fprintf(stderr,"ERROR creating progress thread\n"); exit(0); }
    r = pthread_create(&p2, NULL, Progress, &pc2);
    if(r) { fprintf(stderr,"ERROR creating progress thread\n"); exit(0); }
    r = pthread_create(&p3, NULL, Progress, &pc3);
    if(r) { fprintf(stderr,"ERROR creating progress thread\n"); exit(0); }
    r = pthread_create(&h, NULL, HardWork, NULL);
    if(r) { fprintf(stderr,"ERROR creating worker thread\n"); exit(0); }

    pthread_detach(p1);
    pthread_detach(p2);
    pthread_detach(p3);
    pthread_detach(h);
     printf("stop main\n");
    pthread_exit(0);
}
