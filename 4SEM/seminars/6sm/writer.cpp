#include "msgdata.h"

// Взять сообщение из очереди и вывести на экран 
void writer (int msg_id)
{
    MSG data;
    while(true) {
        // Получаем сообщение из очереди и проверяем на отказ
        if (msgrcv (msg_id, &data, sizeof(MSGDATA), 0, 0) == -1) {
            if (errno == EIDRM) { // Очередь удалена другим процессом
                break; 
            } // иначе какая-то другая ошибка
            fprintf (stderr, "Cannot recieve message\n");
            return;
        }
        // прочиталось нормально 
        if (data.mdata.done) { // проверяем признак конца работы
            break;    // конец работы
        }
        if (data.mdata.msglen) { // есть сообщение для вывода 
            printf ("-> %s\n", data.mdata.msgbuf);
            data.mdata.msglen = 0;
        }
    }
    // финальный отчет
    fprintf (stderr,  "writer process %d exits\n", getpid ());
}

int main ()
{
    int msg_id; // Идентификатор очереди сообщений 
  
    // открываем очередь сообщений и запускаем читателя   
    if ((msg_id = msg_open (MSG_KEY)) == -1) return 1;
    writer (msg_id);

    msg_close (msg_id);
    return 0;
}
