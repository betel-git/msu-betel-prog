#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define AUCTIONEER_PORT 5550
#define BUFLEN 256
#define MAX_BIDDERS 10

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <REG_TIMEOUT> <WAIT_TIMEOUT> <ROUNDS>\n", argv[0]);
        exit(1);
    }

    int REG_TIMEOUT, WAIT_TIMEOUT, ROUNDS;

    if (argc > 1) REG_TIMEOUT = atoi(argv[1]);
    if (argc > 2) WAIT_TIMEOUT = atoi(argv[2]);
    if (argc > 3) ROUNDS = atoi(argv[3]);

    if (REG_TIMEOUT <= 0 || WAIT_TIMEOUT <= 0 || ROUNDS <= 0) {
        fprintf(stderr, "All timeouts and counts must be positive integers.\n");
        exit(1);
    }

    srand(time(NULL));
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(AUCTIONEER_PORT);
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); exit(1); }

    printf("Auctioneer started on port %d\n", AUCTIONEER_PORT);
    printf("Settings: REG_TIMEOUT = %d sec, WAIT_TIMEOUT = %d sec, ROUNDS = %d\n",
           REG_TIMEOUT, WAIT_TIMEOUT, ROUNDS);

    // регистрация участников
    struct sockaddr_in bidders[MAX_BIDDERS];
    int num_bidders = 0;
    char buf[BUFLEN];
    struct timeval tv = {REG_TIMEOUT, 0};
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    printf("Waiting for registrations (%d sec)...\n", REG_TIMEOUT);
    while (num_bidders < MAX_BIDDERS) {
        struct sockaddr_in from;
        socklen_t fromlen = sizeof(from);
        ssize_t n = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&from, &fromlen);
        if (n < 0) break;
        buf[n] = '\0';
        if (strcmp(buf, "REGISTER") == 0) {
            // проверка на дубликаты
            int already = 0;
            for (int i = 0; i < num_bidders; i++) {
                if (bidders[i].sin_port == from.sin_port &&
                    bidders[i].sin_addr.s_addr == from.sin_addr.s_addr) {
                    already = 1;
                    break;
                }
            }
            if (!already) {
                bidders[num_bidders++] = from;
                printf("Registered bidder from port %d\n", ntohs(from.sin_port));
            }
        }
    }
    tv.tv_sec = 0; tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    printf("Registration finished. %d bidders registered.\n", num_bidders);
    if (num_bidders == 0) {
        printf("No bidders. Exiting.\n");
        close(sock);
        return 0;
    }

    // сами торги
    for (int round = 1; round <= ROUNDS; round++) {
        printf("\n========== ROUND %d ==========\n", round);
        int current_max = 100 + rand() % 100;
        struct sockaddr_in leader_addr;
        int leader_port = -1;
        // рассылаем всем, что торги начались
        char start_msg[BUFLEN];
        snprintf(start_msg, BUFLEN, "START %d", current_max);
        for (int i = 0; i < num_bidders; i++) {
            sendto(sock, start_msg, strlen(start_msg)+1, 0,
                   (struct sockaddr*)&bidders[i], sizeof(bidders[i]));
        }
        printf("START price = %d\n", current_max);

        fd_set rset;
        struct timeval timeout;

        while (true) {
            timeout.tv_sec = WAIT_TIMEOUT;
            timeout.tv_usec = 0;
            FD_ZERO(&rset);
            FD_SET(sock, &rset);
            int sel_err = select(sock + 1, &rset, 0, 0, &timeout);
            if (sel_err == -1) {
                perror("select");
                break;
            } else if (sel_err == 0) {
                break;  // бездействие
            }

            struct sockaddr_in from;
            socklen_t fromlen = sizeof(from);
            ssize_t n = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&from, &fromlen);
            if (n < 0) continue;
            buf[n] = '\0';

            if (strncmp(buf, "BID ", 4) == 0) {
                int bid = atoi(buf + 4);
                if (bid > current_max) {
                    current_max = bid;
                    leader_addr = from;
                    leader_port = ntohs(from.sin_port);
                    printf("New leader: port %d with %d\n", leader_port, current_max);
                    char update[BUFLEN];
                    snprintf(update, BUFLEN, "CURRENT_BID %d %d", leader_port, current_max);
                    for (int i = 0; i < num_bidders; i++) {
                        sendto(sock, update, strlen(update)+1, 0,
                               (struct sockaddr*)&bidders[i], sizeof(bidders[i]));
                    }
                }
            }
        }

        // объявление победителя
        char result[BUFLEN];
        if (leader_port != -1) {
            snprintf(result, BUFLEN, "WINNER %d %d", leader_port, current_max);
        } else {
            snprintf(result, BUFLEN, "NO_WINNER");
        }
        for (int i = 0; i < num_bidders; i++) {
            sendto(sock, result, strlen(result)+1, 0,
                   (struct sockaddr*)&bidders[i], sizeof(bidders[i]));
        }
        printf("Result: %s\n", result);
        sleep(1);
    }

    // завершение всех участников
    char end_msg[] = "END";
    for (int i = 0; i < num_bidders; i++) {
        sendto(sock, end_msg, strlen(end_msg)+1, 0,
               (struct sockaddr*)&bidders[i], sizeof(bidders[i]));
    }
    close(sock);
    printf("Auctioneer terminated.\n");
    return 0;
}
