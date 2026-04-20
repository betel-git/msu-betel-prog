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

#define PORT    5555
#define BUFLEN  512
char buf[BUFLEN];

bool  WorkWithClient (int sock);

#define Test(a, s)  if (a<0) { perror(s); exit (EXIT_FAILURE); }


int  main (void)
{
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

    // запускаем цикл обслуживания клиентов
    int new_sock; 
    while(true) {
        size = sizeof(sockaddr_in);
        new_sock = accept(sock, (sockaddr*)&cli_addr, &size);
        Test(new_sock, "Accept")  
        WorkWithClient(new_sock);
    }
    close(sock);
    return 0;
}

bool  WorkWithClient (int sock)
{
#define  endwork  close(sock); return false 
    while(true) {
        // читаем от клиента
        int nbytes = read(sock, buf, BUFLEN);
        if (nbytes < 0) { perror ("Read failure");  endwork; }
        else if (nbytes == 0) {  endwork; }
        else {  fprintf(stdout,"Server gets message: %s\n",buf); }
        
        // если получили стоп-слово, конец работы
        if (strstr(buf, "stop")) { endwork; }
        
        // формируем ответ - для простоты просто дописываем в конец
        strcat (buf, " This is my answer!\n");
        
        // отправляем ответ клиенту
        nbytes = write(sock, buf, strlen(buf)+1);
        fprintf(stdout,"Write back: %s\nnbytes=%d\n", buf, nbytes);
        if ( nbytes<0 ) {  perror ("Write failure.");  endwork; }
    }
    return true;
#undef  endwork
}

