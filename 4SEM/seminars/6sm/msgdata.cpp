#include "msgdata.h"

int msg_open (int key)
{
    int msg_id;   //  результат - id очереди

    // пытаемся открыть очередь сообщений 
    if ((msg_id = msgget (key, 0)) == -1) {
        // Не удалось, рассмотрим причину 
        if (errno == ENOENT) { // очередь сообщений не существует. Создаем ее. 
            if ((msg_id = msgget (key, IPC_CREAT | 0664)) == -1) {
                fprintf (stderr, "Cannot create mesage queue\n");
                return 0;
            }
        } else {
            fprintf (stderr, "Cannot get mesage queue\n");
            return 0;
        }
    }
    return msg_id;
}

int msg_close (int id)
{
    // Удаляем очередь сообщений. Удаление происходит сразу. 
    // Все ожидающие сообщений процессы активизируются, 
    // ожидание завершается с ошибкой EIDRM - Error IDentifier ReMoved. 
    // Вся последующая работа с этой очередью будет давать ошибку, 
    // поэтому возвращаемое значение функции не проверяется. 
    msgctl (id, IPC_RMID, 0);
    return 0;
}

