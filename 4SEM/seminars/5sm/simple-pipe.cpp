#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define msg_length  128 

int  pipe_fd[2];   // pipe descriprtors: [0] reading, [1] writing

void child_process()
{
    // we write to pipe, so close reading
    close(pipe_fd[0]);

    sleep(2);
    char msg[64];
    strcpy(msg, "Some message from child\n");
    int ret = write (pipe_fd[1], msg, strlen(msg) + 1);
    if (ret < 0) { perror("child"); }
    else { printf("child: send the message of %d bytes\n", ret); }
    close(pipe_fd[1]);
}


int main()
{
    // message buffer
    char msg[msg_length];

    // create the pipe
    int ret = pipe(pipe_fd);
    if (ret == -1) { fprintf(stderr, "pipe ERROR\n"); exit(0); }

    // fork the process
    printf("fork process \n");
    pid_t  id = fork();
    if (id == -1) {
        fprintf(stderr,"fork ERROR\n");
        return -1;
    } else if (id == 0) {
        // here we in child process
        child_process();
        return 0;
    } 
    // here we in parent process
    // we read from pipe, so close writing end
    close(pipe_fd[1]);

    // try to read from pipe
    ret = read(pipe_fd[0], msg, msg_length);
    printf("parent read %d bytes\n", ret);
    if (ret > 0) printf("message: %s\n", msg);
    close(pipe_fd[0]);

    // wait for child to terminate
    waitpid(id, 0, 0);
    return 0;
}


