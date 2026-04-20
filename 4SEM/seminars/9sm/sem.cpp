#include <stdio.h>
#include <sys/select.h>
#include <stdlib.h>

int randval() {return double(rand())/RAND_MAX * 10;}

int main()
{
    fd_set rset;
    FD_SET(0, &rset);
    int a,b,c;

    struct timeval t;
    for (int i = 0; i < 10; i++) {
        t.tv_sec = 2;
        t.tv_usec = 0;
        a = randval();
        b = randval();
        printf("%d + %d?\n", a, b);
        FD_ZERO(&rset);
        FD_SET(0, &rset);
        select(1, &rset, 0, 0, &t);
        printf("%ld %ld\n", t.tv_sec, t.tv_usec);

        if (FD_ISSET(0, &rset)) {
            if (scanf("%d", &c) != 1) return -1;
            if (c == a + b) {
                printf("success!\n");
            } else {
                printf("error!\n");
            }
        } else {
            printf("time is over\n");
        }
    }
    return 0;
}