#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define PORT_SERVER 5550
#define BLOCK_SIZE 512
#define TIMEOUT_SEC 2
#define MAX_RETRIES 5

struct Packet {
    uint32_t block_num;
    uint32_t total_blocks;
    uint32_t data_size;
    char data[BLOCK_SIZE];
};

void send_file(int sock, struct sockaddr_in client_addr, const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("File '%s' not found\n", filename);
        return;
    }

    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint32_t total_blocks = (file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    if (file_size == 0) total_blocks = 1;

    struct Packet pkt;
    uint32_t current_block = 0;

    while (current_block < total_blocks) {
        // читаем блок
        fseek(f, current_block * BLOCK_SIZE, SEEK_SET);
        size_t bytes_read = fread(pkt.data, 1, BLOCK_SIZE, f);

        pkt.block_num = htonl(current_block);
        pkt.total_blocks = htonl(total_blocks);
        pkt.data_size = htonl((uint32_t)bytes_read);

        int retries = 0;
        int acked = 0;

        while (retries < MAX_RETRIES && !acked) {
            sendto(sock, &pkt, sizeof(pkt), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

            struct timeval tv = {TIMEOUT_SEC, 0};
            setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

            uint32_t ack;
            ssize_t n = recvfrom(sock, &ack, sizeof(ack), 0, NULL, NULL);
            if (n == sizeof(ack) && ntohl(ack) == current_block) {
                acked = 1;
                printf("Block %u acknowledged\n", current_block);
            } else {
                retries++;
                printf("Retry %d for block %u\n", retries, current_block);
            }
        }

        if (!acked) {
            printf("Failed to deliver block %u\n", current_block);
            break;
        }
        current_block++;
    }

    fclose(f);
    printf("File transfer finished\n");
}

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT_SERVER);

    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind"); exit(1);
    }

    printf("Server listening on port %d\n", PORT_SERVER);

    while (1) {
        char filename[256];
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        ssize_t n = recvfrom(sock, filename, sizeof(filename) - 1, 0,
                             (struct sockaddr*)&client_addr, &client_len);
        if (n <= 0) continue;
        filename[n] = '\0';
        printf("Request from %s:%d: %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), filename);

        send_file(sock, client_addr, filename);
    }

    close(sock);
    return 0;
}