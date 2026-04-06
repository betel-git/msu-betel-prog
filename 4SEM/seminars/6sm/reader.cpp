#include "msgdata.h"

// Прочитать сообщение с терминала и записать в очередь 
void reader (int msg_id)
{
    MSG data;
    while(true) {
        // Выход по Ctrl+D 
        if (!fgets (data.mdata.msgbuf, BUF_LEN, stdin)) break;
        data.mdata.msglen = strlen (data.mdata.msgbuf) + 1;  // длина сообщения
        data.mdata.done = 0;
        data.mtype = 1;
        // Посылаем сообщение в очередь с проверкой успешности
        if (msgsnd (msg_id, &data, sizeof(MSGDATA), 0) == -1) {
            perror ("send");
            fprintf (stderr, "Cannot send message\n");
            return;
        }
    }
    // после прерывания цикла дадим указание закончить работу: data.done = 1; 
    data.mtype = 1;
    data.mdata.done = 1;
    data.mdata.msglen = 0; 
    if (msgsnd (msg_id, &data, sizeof(MSGDATA), 0) == -1) {
        fprintf (stderr, "Cannot send message\n");
        return;
    }
    // финальный отчет
    fprintf (stderr, "reader process %d exits\n", getpid());
}

int main ()
{
    int msg_id; // Идентификатор очереди сообщений 

    // открывам очередь и запускаем читателя
    if ((msg_id = msg_open (MSG_KEY)) == -1) return 1;
    reader (msg_id);

    msg_close (msg_id);
    return 0;
}
