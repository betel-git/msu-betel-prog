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
#define MAX_STUDENTS 10

struct Student {
    struct sockaddr_in addr;
    int replied;
};

int main() {
    srand(time(NULL));

    int student_ports[] = {5551, 5552, 5553};
    int num_students = sizeof(student_ports) / sizeof(student_ports[0]);

    struct Student students[MAX_STUDENTS];
    for (int i = 0; i < num_students; i++) {
        memset(&students[i].addr, 0, sizeof(struct sockaddr_in));
        students[i].addr.sin_family = AF_INET;
        students[i].addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        students[i].addr.sin_port = htons(student_ports[i]);
        students[i].replied = 0;
    }

    // Создаём сокет учителя
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    // Привязываемся к порту учителя
    struct sockaddr_in teacher_addr;
    teacher_addr.sin_family = AF_INET;
    teacher_addr.sin_addr.s_addr = INADDR_ANY;
    teacher_addr.sin_port = htons(TEACHER_PORT);
    if (bind(sock, (struct sockaddr*)&teacher_addr, sizeof(teacher_addr)) < 0) {
        perror("bind");
        exit(1);
    }

    char question[] = "Question?";
    char answer[BUFLEN];

    for (int round = 1; round <= 3; round++) {
        printf("\n=== Round %d ===\n", round);

        for (int i = 0; i < num_students; i++) {
            sendto(sock, question, strlen(question) + 1, 0,
                   (struct sockaddr*)&students[i].addr, sizeof(students[i].addr));
            printf("Sent to student on port %d\n", ntohs(students[i].addr.sin_port));
            students[i].replied = 0;
        }

        int repl_cnt = 0;
        while (repl_cnt < num_students) {
            struct sockaddr_in from_addr;
            socklen_t from_len = sizeof(from_addr);
            ssize_t n = recvfrom(sock, answer, BUFLEN, 0,
                                  (struct sockaddr*)&from_addr, &from_len);
            if (n < 0) {
                perror("recvfrom");
                continue;
            }
            answer[n] = '\0';
            int port = ntohs(from_addr.sin_port);
            printf("Reply from port %d: %s\n", port, answer);

            for (int i = 0; i < num_students; i++) {
                if (ntohs(students[i].addr.sin_port) == port && !students[i].replied) {
                    students[i].replied = 1;
                    repl_cnt++;
                    break;
                }
            }
        }
        printf("All %d students replied for round %d\n", repl_cnt, round);
        sleep(1);
    }

    close(sock);
    return 0;
}