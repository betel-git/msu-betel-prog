#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define AUCTIONEER_PORT 5550
#define BUFLEN 256

int main() {
    srand(time(NULL));
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(0);   // автоматически определяется порт
    if (bind(sock, (struct sockaddr*)&my_addr, sizeof(my_addr)) < 0) { perror("bind"); exit(1); }
    // узнаём свой порт
    socklen_t len = sizeof(my_addr);
    getsockname(sock, (struct sockaddr*)&my_addr, &len);
    int my_port = ntohs(my_addr.sin_port);
    printf("Bidder started on port %d\n", my_port);

    struct sockaddr_in auct_addr;
    auct_addr.sin_family = AF_INET;
    auct_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    auct_addr.sin_port = htons(AUCTIONEER_PORT);

    // регистрируемся
    char reg[] = "REGISTER";
    sendto(sock, reg, strlen(reg) + 1, 0, (struct sockaddr*)&auct_addr, sizeof(auct_addr));
    printf("Registered\n");

    char buf[BUFLEN];
    socklen_t addr_len = sizeof(auct_addr);
    int my_limit = 0;          // максимальная сумма, которую участник готов потратить
    int in_round = 0;

    while (true) {
        ssize_t n = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&auct_addr, &addr_len);
        if (n < 0) { perror("recvfrom"); break; }
        buf[n] = '\0';

        if (strncmp(buf, "START ", 6) == 0) { // старт торгов
            int start_price = atoi(buf+6);
            printf("\n=== New round ===\nStart price: %d\n", start_price);
            in_round = 1;
            // определяем свой лимит
            my_limit = rand() % 1000;
            printf("My limit: %d\n", my_limit);
            if (my_limit > start_price) {
                usleep((rand() % 2000000)); // думаем 0-2 секунды
                int my_bid = start_price + 1 + rand() % (my_limit - start_price);
                char bid_msg[BUFLEN];
                snprintf(bid_msg, BUFLEN, "BID %d", my_bid);
                sendto(sock, bid_msg, strlen(bid_msg)+1, 0,
                       (struct sockaddr*)&auct_addr, addr_len);
                printf("Placed first bid: %d\n", my_bid);
            } else {
                printf("I'm not interested (limit <= start price)\n");
            }
        }
        else if (strncmp(buf, "CURRENT_BID ", 12) == 0) {
            if (!in_round) continue;
            int leader_port, leader_bid;
            sscanf(buf + 12, "%d %d", &leader_port, &leader_bid);
            if (leader_port != my_port && leader_bid < my_limit) {
                usleep((rand() % 150000)); // надо подумать
                int new_bid = leader_bid + 1 + (0.1 * leader_bid);
                char bid_msg[BUFLEN];
                snprintf(bid_msg, BUFLEN, "BID %d", new_bid);
                sendto(sock, bid_msg, strlen(bid_msg)+1, 0,
                       (struct sockaddr*)&auct_addr, addr_len);
                printf("Raised bid to %d\n", new_bid);
            }
        }
        else if (strncmp(buf, "WINNER ", 7) == 0) {
            int winner_port, winning_bid;
            sscanf(buf+7, "%d %d", &winner_port, &winning_bid);
            if (winner_port == my_port)
                printf("*** I WON with %d! ***\n", winning_bid);
            else
                printf("Winner: port %d with %d\n", winner_port, winning_bid);
            in_round = 0;
        }
        else if (strcmp(buf, "NO_WINNER") == 0) {
            printf("No winner this round.\n");
            in_round = 0;
        }
        else if (strcmp(buf, "END") == 0) {
            printf("END received. Exiting.\n");
            break;
        }
    }

    close(sock);
    printf("Bidder %d terminated.\n", my_port);
    return 0;
}
