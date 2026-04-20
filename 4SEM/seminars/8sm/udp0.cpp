#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#define  PORT_THIS      5550 // номер порта выбирается самостоятельно
#define  BUFLEN         512
char     buf[BUFLEN];

// печать адресной структуры для наглядности
void PrintAddr(const sockaddr_in &addr, const char *text);

int main(void)
{
    int sock;              // ID сокета

    int  err;       
    size_t  size;
    ssize_t  nbytes;

    // адресные структуры
    sockaddr_in addr_this;    // этот компьютер
    sockaddr_in addr_other;   // другой абонент

    // заполняем адресные структуры
    hostent *hostinfo;
    hostinfo = gethostbyname("127.0.0.1");    // адрес обратной связи
    if ( hostinfo == nullptr ) {
        fprintf (stderr, "Unknown host\n");
        exit (EXIT_FAILURE);
    }
    addr_this.sin_family = AF_INET;           // address family Internet
    addr_this.sin_addr.s_addr = INADDR_ANY;   // любой интерфейс этой машины
    addr_this.sin_port = htons(PORT_THIS);    // порт преобразуется в сетевой byte order

    socklen_t ssize = sizeof(addr_other);     

    // Создаем UDP сокет.
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if ( sock<0 ) {
        perror ("Socket was not created");
        exit (EXIT_FAILURE);
    }
    // SOCK_DGRAM означает именно UDP сокет
    // Разрешаем немедленное переиспользование сокета
    int opt = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    // Привязываем сокет к сетевому интерфейсу
    err = bind(sock, (sockaddr*)&addr_this, sizeof(addr_this));
    if ( err<0 ) {
        perror ("Cannot bind socket");
        exit (EXIT_FAILURE);
    }

    // бесконечный цикл работы с сообщениями
    while (true) {

        // пытаемся прочитать входящее сообщение 
        buf[0] = 0;
        nbytes = recvfrom(sock, buf, BUFLEN, 0, (sockaddr*)&addr_other, &ssize);
        PrintAddr(addr_other, "get message from\n");
        printf("message %ld bytes:\n%s\n", nbytes, buf);

        // читаем с клавиатуры ответ и отсылаем его
        printf(" > ");
        fgets(buf, BUFLEN, stdin);
        size = strlen(buf) + 1;
        nbytes = sendto(sock, buf, size, 0, (sockaddr*)&addr_other, ssize);
     
        // проверяем как отослалось
        if( nbytes<0 || (int)nbytes != (int)size ) {
            perror("Send:");
            close(sock);
            exit (EXIT_FAILURE);
        } else {
            printf("sending message of %ld bytes\n", nbytes);
        }
    }

    // конец работы
    close(sock);
    return 0;
}

void PrintAddr(const sockaddr_in &addr, const char *text)
{
    if (text) printf("%s", text);
    printf("type %d port %d ip addr %s\n", 
        int(addr.sin_family), ntohs(int(addr.sin_port)), inet_ntoa(addr.sin_addr));
}


