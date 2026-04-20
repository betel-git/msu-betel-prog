#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define  SERVER_PORT     5555
#define  SERVER_NAME    "127.0.0.1"
#define  BUFLEN          512
char buf[BUFLEN];

int  WorkWithServer  (int fd);

int  main (void)
{
    int err;
    int sock;
    struct sockaddr_in server_addr;
    struct hostent    *hostinfo;

    // заполняем адресные структуры
    hostinfo = gethostbyname(SERVER_NAME);
    if ( hostinfo==NULL ) { perror("Host."); exit (EXIT_FAILURE); }

    server_addr.sin_family = PF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(in_addr*) hostinfo->h_addr;

    // Создаем TCP сокет.
    sock = socket(PF_INET, SOCK_STREAM, 0); 
    if ( sock<0 ) { perror ("Socket."); exit (EXIT_FAILURE); }

    // Запрашиваем соединение с сервером
    err = connect (sock, (sockaddr*)&server_addr, sizeof(server_addr));
    if ( err<0 ) { perror ("Connect."); exit (EXIT_FAILURE); }
    fprintf (stdout,"Connection is ready\n");

    // Обмениваемся данными
    while(true) {
        if (WorkWithServer(sock) < 0) break;
    }
    fprintf (stdout,"The end\n");

    // Закрываем socket
    close (sock);
    exit (EXIT_SUCCESS);
}

int  WorkWithServer (int fd)
{
    // берем строку с клавиатуры
    fprintf(stdout,"Send to server > ");
    fgets(buf, BUFLEN, stdin);   

    // отсылаем на сервер
    int nbytes = write (fd, buf, strlen(buf)+1);
    if (strstr(buf,"stop")) return -1;
    if ( nbytes<0 ) { perror("write"); return -1; }
    if (strstr(buf, "stop")) return -1;
    
    // получаем ответ от сервера и печатаем его на экран
    nbytes = read(fd, buf, BUFLEN);
    if (nbytes < 0) { perror ("read");  return -1;  } 
    else if (nbytes == 0) { fprintf (stderr, "Client: no message\n"); }
    else { fprintf (stdout,"Server's replay: %s\n",buf); }
    return 0;
}


