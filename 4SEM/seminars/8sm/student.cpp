#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define TEACHER_PORT 5550
#define BUFLEN 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <my_port>\n", argv[0]);
        exit(1);
    }
    int my_port = atoi(argv[1]);
    srand(time(NULL) ^ my_port);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(my_port);
    if (bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    struct sockaddr_in teacher_addr;
    teacher_addr.sin_family = AF_INET;
    teacher_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    teacher_addr.sin_port = htons(TEACHER_PORT);

    char buf[BUFLEN];
    char reply[BUFLEN];
    socklen_t addr_len = sizeof(teacher_addr);

    printf("Student on port %d started, waiting for questions...\n", my_port);

    while (true) {
        ssize_t n = recvfrom(sock, buf, BUFLEN, 0, NULL, NULL);
        if (n < 0) {
            perror("recvfrom");
            break;
        }
        buf[n] = '\0';
        printf("Received: %s\n", buf);

        int delay = rand() % 3000000;
        usleep(delay);

        // Отправляем ответ
        snprintf(reply, BUFLEN, "Answer from port %d (delay %.2f sec)",
                 my_port, delay / 1000000.0);
        sendto(sock, reply, strlen(reply) + 1, 0,
               (struct sockaddr*)&teacher_addr, addr_len);
        printf("Sent reply after %.2f seconds\n", delay / 1000000.0);
    }

    close(sock);
    return 0;
}
