#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <cmath>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Комментарии TODO показывают где разумно вставлять соответствующие операции.
// Эти операции вы должны реализовать самостоятельно.


const static int MSG_KEY = 1234;     // пример ключа очереди сообщений

const static double  EPS = 1.e-50;   // уровень проверки на 0 (для простоты)

struct MSGDATA   // содержательные данные сообщения, одинаковые для задания и для ответа
{                                                  
    long proc_id;  // идентификатор процесса
    long eqn_id;   // номер уравнения
    int  rcount;   // количество корней
    double r[3];   // коэффициенты (вход) или корни (выход, два первых элемента)
};

struct MSG 
{
    long type;     // тип сообщения
    MSGDATA data;  // данные
};

unsigned RandomTime()   // случайное время для задержки
{
    unsigned t = 1000000 + float(rand())/RAND_MAX * 1000000;
    return t;
}

// простейший решатель квадратного уравнения
// return - количество действительных корней

int  Solver (double *coef, double *root)   // coef[3]  root[2]
{
    usleep(RandomTime());    
    double a = coef[0], b = coef[1], c = coef[2];
    if (fabs(a) < EPS) { return -1; } // отказываемся решать не квадратные уравнения !  
    double d = b*b - 4*a*c;
    if (d < 0) { return 0; } 
    b /= 2*a;
    c /= a;
    d = sqrt(d)/(2*a);
    if (b > 0) { root[0] = -b - d; }
    else { root[0] = -b + d; }          
    root[1] = c/root[0];
    return (fabs(root[0] - root[1]) < EPS) ? 1 : 2;
}

void SolverProcess(int id)   // id - идентификатор данного процесса
{
    // TODO открываем необходимые очереди сообщений

    while(true) {
        // TODO получаем сообщение с заданием:
        //   - коэффициентами и номером уравнения
        //   - либо указанием закончить работу (тогда break)

        // TODO решаем уравнение и заполняем сообщение с ответом

        // TODO отправляем сообщение с ответом
    }
}


int main(int argc, char **argv)
{
    // в командной строке задается количество процессов 
    // и имена входного (коэффициенты) и выходного (ответы) файлов
    if (argc < 4) {
        fprintf(stderr, "Usage: ./solver  num_processes  in_file  out_file\n");
        return -1;
    }
    int nproc = atoi(argv[1]);
    FILE *fin = fopen(argv[2], "r");
    if (!fin) { fprintf(stderr, "Cannot open %s\n", argv[2]);  return -1; }
    FILE *fout = fopen(argv[3], "w");
    if (!fout) { fclose(fin);  fprintf(stderr, "Cannot open %s\n", argv[3]);  return -1; }
    printf("start main process\n");

    // TODO открываем необходимые очереди сообщений

    // запускаем процессы через fork
    printf("fork processes\n");
    pid_t  p;
    for (int i=0; i<nproc; i++) {
        p = fork();
        if (p < 0) {
            fprintf(stderr,"fork ERROR\n");
            return -1;
        } else if (p == 0) {
        // порожденный процесс
            SolverProcess(i);
            printf("child process terminated\n");
            return 0;
        } 
        // родительский процесс продолжает цикл
    }

    // теперь можно выдавать задания и получать результаты

    MSG msg;    // структура для сообщения

    // читаем строки из файла данных
    while (fscanf(fin,"%d%lf%lf%lf", &msg.data.eqn_id, &msg.data.r[0], &msg.data.r[1], &msg.data.r[2]) == 4) {
        // тестовая проверка, что решатель решает правильно 
        //int k = Solver(msg.data.r, msg.data.r);
        //if (k>0) fprintf(fout, "%4d  %10.4f %10.4f\n", i, msg.data.r[0], msg.data.r[1]);
        //else     fprintf(fout, "%4d  no solution\n", i);
       
        // TODO тут уже действуем по выбранной логике
        //      выдачи заданий и получения ответов ***
    }

    // TODO если все задания выданы и все ответы получены, 
    //      то нужно всем решателям скомандовать закончить работу

    // TODO теперь можно закрыть открытые очереди сообщений

    // TODO на всякий случай надо выполнить wait для всех
    //      порожденных процессов, чтобы не осталось зомби

    // TODO тут можно напечатать окончательный протокол кто сколько задач решил
    //      эту информацию нужно собрать где-то на предыдущих этапах.

    fclose(fin);
    fclose(fout);
    return 0;
}




                                                            