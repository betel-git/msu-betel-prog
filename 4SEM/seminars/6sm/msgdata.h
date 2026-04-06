#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_LEN 256
    
struct MSGDATA 
{  
   char msgbuf[BUF_LEN];  // буфер сообщения 
   int done;              // признак окончания работы 
   int msglen;            // длина сообщения 
};

struct MSG 
{  // Первое поле должно быть именно таким для задания типа сообщения
   // второе поле используется собственно для хранения сообщения, его можно определять в любой форме
   long int mtype;        // тип сообщения (любое >0)
   MSGDATA mdata;         // собственно сообщение 
};

// Условный номер (ключ) очереди сообщений 
#define MSG_KEY 1223      // любое по нашему выбору

int msg_open (int key);
int msg_close (int id);
