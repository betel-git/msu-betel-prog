#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut_read = PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t mut_write = PTHREAD_MUTEX_INITIALIZER;

#define TEXT_LEN  1024
char text[TEXT_LEN];              //  общий буфер для обмена текстами
                                                   

void *Reader(void *arg)
{
    int ret;
    char buf[TEXT_LEN];   // внутренний буфер читателя
    while(true) {

        // блокируем доступ к тексту только для себя и читаем его
        ret = pthread_mutex_lock(&mut_read);
        if(ret) { fprintf(stderr,"Reader: read lock\n"); exit(0); }
        printf("      Reader:  reading text: %s\n", text);
        strcpy(buf, text);
        text[0] = 0;        // "уничтожаем" исходный текст
 
       // все прочитали, можно освободить для других
        ret = pthread_mutex_unlock(&mut_read);
        if(ret) { fprintf(stderr,"Reader: cannot unlock read %d\n", ret); perror(""); exit(0); }

        // разрешаем писателю записать новый текст
        ret = pthread_mutex_unlock(&mut_write);
        if(ret) { fprintf(stderr,"Reader: cannot unlock write\n"); exit(0); }

        // обрабатываем прочитанный текст
        printf("      Reader:  thinking over it\n");
        sleep(1);
    }
    return NULL;
}

void *Writer(void * arg)
{
    int cnt = 0, ret;
    char buf[TEXT_LEN];

    while (true) {
        // блокируемся до возможности писать следующий текст (пока не будет прочитан предыдущий)
        ret = pthread_mutex_lock(&mut_write);
        if(ret) { fprintf(stderr,"Writer: cannot lock write\n"); exit(0); }

        // готовим очередной текст
        printf("Writer:  preparing text no.%d\n", ++cnt);
        sprintf(buf, "Text no.%d", cnt);

        // монопольно записываем в буфер
        ret = pthread_mutex_trylock(&mut_read);
        if(ret) { fprintf(stderr,"Writer: already locked, so we can write\n"); }
        printf("Writer:  writing text for people to read\n");
        strcpy(text, buf);
        ret = pthread_mutex_unlock(&mut_read);
        if(ret) { fprintf(stderr,"Writer: cannot unlock read\n"); exit(0); }
    }
}

int main()
{
    int ret;

    // запрещаем читателям читать, так как текстов еще писатели не написали
    ret = pthread_mutex_lock(&mut_read);
    if(ret) { fprintf(stderr,"Reader: cannot iniitially lock read %d\n", ret); perror(""); exit(0); }

    // создаем потоки для читателей и писателей
    printf("Start\n");
    pthread_t r, w;

    ret = pthread_create(&w, NULL, Writer, NULL);
    if(ret) { fprintf(stderr,"ERROR creating writer\n"); exit(0); }
    printf("Writer ready\n");

    ret = pthread_create(&r, NULL, Reader, NULL);
    if(ret) { fprintf(stderr,"ERROR creating reader\n"); exit(0); }
    printf("Reader ready\n");

    // даем им возможность поработать 10 секунд
    sleep(10);

    // все уничтожаем
    pthread_cancel(r);
    pthread_cancel(w);
    pthread_mutex_destroy(&mut_read);
    pthread_mutex_destroy(&mut_write);

    return 0;
}
