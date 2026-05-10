#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <math.h>

const static double EPS = 1.e-50;
#define PORT 5555

struct Roots {
    double r1, r2;
    int res;
};

#define Test(a, s) if (a < 0) { perror(s); exit(EXIT_FAILURE); }

Roots Solver (double a, double b, double c) {
    Roots r;
    double D = b*b - 4*a*c;

    if (fabs(a) < EPS) {
        r.res = 0;
    } else if (D < 0) {
        r.res = 0;
    } else if (fabs(D) < EPS) {
        r.res = 1;
        r.r1 = -b / (2*a);
    } else {
        r.res = 2;
        r.r1 = (-b + sqrt(D)) / (2*a);
        r.r2 = (-b - sqrt(D)) / (2*a);
    }
    return r;
}

// легаси
int WorkWithClient(int sock) {
    double coeffs[3];

    while (true) {
        int nbytes = read(sock, coeffs, sizeof(coeffs));

        if (nbytes < 0) {
            perror("Read failure");
            close(sock);
            return -1;
        }
        else if (nbytes == 0) {
            printf("Client disconnected\n");
            close(sock);
            return -1;
        }

        printf("Received: a = %lf b = %lf c = %lf\n",
               coeffs[0], coeffs[1], coeffs[2]);

        Roots r = Solver(coeffs[0], coeffs[1], coeffs[2]);

        nbytes = write(sock, &r, sizeof(r));
        if (nbytes < 0) {
            perror("Write failure");
            close(sock);
            return -1;
        }
    }
}

// актуальная версия
int WorkWithClient2(int sock) {
    double coeffs[3];

    while (1) {
        int nbytes = read(sock, coeffs, sizeof(coeffs));

        if (nbytes < 0) {
            perror("Read failure");
            break;
        }
        else if (nbytes == 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("PID %d: a=%lf b=%lf c=%lf\n",
               getpid(), coeffs[0], coeffs[1], coeffs[2]);

        Roots r = Solver(coeffs[0], coeffs[1], coeffs[2]);

        nbytes = write(sock, &r, sizeof(r));
        if (nbytes < 0) {
            perror("Write failure");
            break;
        }
    }

    close(sock);
    return 0;
}

int main() {
    int sock, new_sock;
    struct sockaddr_in addr, cli_addr;
    socklen_t size;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    Test(sock, "Main socket");

    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int err = bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    Test(err, "Bind");

    err = listen(sock, 7);
    Test(err, "Listen");

    printf("Server started on port %d\n", PORT);

    while (true) {
        size = sizeof(cli_addr);
        new_sock = accept(sock, (struct sockaddr*)&cli_addr, &size);
        Test(new_sock, "Accept");

        printf("Client connected\n");

        //WorkWithClient(new_sock);


        // вот отсюда комментировать
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            close(new_sock);
            continue;
        }

        if (pid == 0) {
            close(sock);
            WorkWithClient2(new_sock);
            exit(0);
        }
        else {
            close(new_sock);
        }
    }
    //wait(0);


    close(sock);
    return 0;
}
