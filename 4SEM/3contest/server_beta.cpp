#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <cmath>

#define PORT 5555
#define MAX_CLIENTS 100

struct Roots {
    double r1, r2;
    int res;
};

Roots Solver (double a, double b, double c) {
    Roots r;
    double D = b * b - 4 * a * c;

    if (a == 0) {
        r.res = 0;
        return r;
    }

    if (D < 0) {
        r.res = 0;
    } else if (D == 0) {
        r.res = 1;
        r.r1 = -b / (2 * a);
    } else {
        r.res = 2;
        r.r1 = (-b + sqrt(D)) / (2 * a);
        r.r2 = (-b - sqrt(D)) / (2 * a);
    }
    return r;
}

#define Test(a, s)  if (a<0) { perror(s); exit (EXIT_FAILURE); }

int main() {
    int     err, opt=1;
    int     sock;
    socklen_t    size;
    sockaddr_in  addr;
    sockaddr_in  cli_addr;
 
    // Создаем TCP сокет для приема запросов на соединение
    sock = socket (PF_INET, SOCK_STREAM, 0);
    Test(sock, "Main socket")
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt,sizeof(opt));

    // Заполняем адресную структуру 
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(sock, (sockaddr*)&addr, sizeof(addr));
    Test(err, "Bind")

    // Создаем очередь на 3 входящих запроса соединения
    err = listen(sock,3);
    Test(err, "Listen")
    }

    FD_ZERO(&master_set);
    FD_SET(server_fd, &master_set);

    max_fd = server_fd;

    std::cout << "Server started on port " << PORT << std::endl;

    while (true) {
        read_fds = master_set;

        if (select(max_fd + 1, &read_fds, 0, 0, 0) < 0) {
            perror("select");
            break;
        }

        for (int i = 0; i <= max_fd; i++) {
            if (FD_ISSET(i, &read_fds)) {

                // новый клиент
                if (i == server_fd) {
                    new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
                    if (new_socket < 0) {
                        perror("accept");
                        continue;
                    }

                    FD_SET(new_socket, &master_set);
                    if (new_socket > max_fd) max_fd = new_socket;

                    std::cout << "New client connected: " << new_socket << std::endl;
                }
                else {
                    // работа с клиентом
                    double coeffs[3];
                    int bytes = read(i, coeffs, sizeof(coeffs));

                    if (bytes <= 0) {
                        std::cout << "Client disconnected: " << i << std::endl;
                        close(i);
                        FD_CLR(i, &master_set);
                    } else {
                        Roots r = Solver(coeffs[0], coeffs[1], coeffs[2]);

                        write(i, &r, sizeof(r));
                    }
                }
            }
        }
    }

    close(server_fd);
    return 0;
}