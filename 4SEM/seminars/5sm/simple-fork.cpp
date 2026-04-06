#include <unistd.h>
#include <stdio.h>


int main()
{
    printf("start main process\n");

    printf("fork process 1\n");
    pid_t  id1 = fork();
    if (id1 < 0) {
        fprintf(stderr,"fork 1 ERROR\n");
        return -1;
    } else if (id1 == 0) {
        // здесь код порожденного процесса, поработали и завершаем его
        for (int i=0; i<10; i++) {
            sleep(1);
            printf("process1: %d\n", i);
        } 
        return 0;
    } 
    // здесь код родительского процесса, продолжаем работу в нем
    // еще один порожденный ......
    printf("fork success for process 1\n");
    printf("fork process 2\n");
    pid_t  id2 = fork();
    if (id2 < 0) {
        fprintf(stderr,"fork 2 ERROR\n");
        return -1;
    } else if (id2 == 0) {
        // здесь код порожденного процесса, поработали и завершаем его
        for (int i=0; i<6; i++) {
            sleep(2);
            printf("           process2: %d\n", i);
        } 
        return 0;
    }
    // опять код родительского процесса
    sleep(3);
    printf("end main process\n");
    return 0;
}
