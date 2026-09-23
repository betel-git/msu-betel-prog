#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#define SERVER_PORT 5555
#define SERVER_NAME    "127.0.0.1"

struct Roots {
    double r1, r2;
    int res;
};

double rnd() {
    return double(rand())/RAND_MAX * 40 - 20;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printf("Usage: ./cli <port> <count> <output_file>\n");
        return 1;
    }

    int port = atoi(argv[1]);
    int count = atoi(argv[2]);
    const char *outfile = argv[3];

    int err, sock;
    struct sockaddr_in server_addr;
    struct hostent *hostinfo;

    FILE *fout = fopen(outfile, "r");
    if (!fout) {
        perror("fopen");
        exit (EXIT_FAILURE);
    }

    hostinfo = gethostbyname(SERVER_NAME);
    if ( hostinfo==NULL ) { perror("Host."); exit (EXIT_FAILURE); }

    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(in_addr*) hostinfo->h_addr;

    sock = socket(PF_INET, SOCK_STREAM, 0); 
    if ( sock<0 ) { perror ("Socket."); exit (EXIT_FAILURE); }

    err = connect (sock, (sockaddr*)&server_addr, sizeof(server_addr));
    if ( err<0 ) { perror ("Connect."); exit (EXIT_FAILURE); }
    fprintf (stdout,"Connection is ready\n");




    srand(time(NULL));

    double a,b,c;
    for (int i = 0; i < count; i++) {
        a = rnd();
        b = rnd();
        c = rnd();
        double coeffs[3] = {a,b,c};
        write(sock, coeffs, sizeof(coeffs));

        Roots r;
        read(sock, &r, sizeof(r));

        fprintf(fout, "Equation: %lg x^2 + %lg x + %lg\n", a,b,c);
        fprintf(fout, "Result: %d, roots: %lg, %lg\n\n", r.res, r.r1, r.r2); 
    }


    close(sock);
    return 0;
}