#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define PORT_SERVER 5550
#define BLOCK_SIZE 512
#define TIMEOUT_SEC 5

struct Packet {
    uint32_t block_num;
    uint32_t total_blocks;
    uint32_t data_size;
    char data[BLOCK_SIZE];
};

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("socket"); exit(1); }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT_SERVER);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    char filename[256];
    printf("Enter filename: ");
    scanf("%255s", filename);

    sendto(sock, filename, strlen(filename), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

    char outname[512];
    snprintf(outname, sizeof(outname), "downloaded_%s", filename);
    FILE *out = fopen(outname, "wb");
    if (!out) { perror("fopen"); exit(1); }

    uint32_t expected_block = 0;
    struct Packet pkt;
    int finished = 0;

    while (!finished) {
        struct timeval tv = {TIMEOUT_SEC, 0};
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

        ssize_t n = recvfrom(sock, &pkt, sizeof(pkt), 0, NULL, NULL);
        if (n < 12) {  // 3 * uint32_t = 12 байт
            printf("Timeout or incomplete packet\n");
            break;
        }

        uint32_t b_num = ntohl(pkt.block_num);
        uint32_t total = ntohl(pkt.total_blocks);
        uint32_t d_size = ntohl(pkt.data_size);

        if (b_num == expected_block) {
            fwrite(pkt.data, 1, d_size, out);
            printf("Received block %u/%u (%u bytes)\n", b_num + 1, total, d_size);

            uint32_t ack = htonl(b_num);
            sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

            expected_block++;
            if (expected_block >= total) {
                printf("All blocks received\n");
                finished = 1;
            }
        } else if (b_num < expected_block) {
            uint32_t ack = htonl(b_num);
            sendto(sock, &ack, sizeof(ack), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        } else {
            // пропущен блок – теоретически не должно быть, но можно просто игнорировать
            printf("Unexpected block %u, expected %u\n", b_num, expected_block);
        }
    }

    fclose(out);
    close(sock);
    printf("File saved as %s\n", outname);
    return 0;
}