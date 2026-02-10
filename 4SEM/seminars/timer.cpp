#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

int total = 0;

void *Timer(void *arg)
{
    for (int i=0; i < 30; i++) {
        total = i;
        printf("timer %d\n", i);
        sleep(1);
    } 
    return NULL;
}

int main()
{
    pthread_t t;
    auto r = pthread_create(&t, NULL, Timer, NULL);
    if(r) { fprintf(stderr,"ERROR creating timer\n"); exit(0); }

    for (int k = 0; k<5; k++) {
        sleep(2);
        printf("total time %d\n", total);
    } 
    pthread_join(t, NULL);
    printf("end main\n");

//    pthread_detach(t);
//    pthread_cancel(t);
//    pthread_exit(0);
    return 0;
}