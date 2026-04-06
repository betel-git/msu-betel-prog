#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <cmath>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <vector>

// Комментарии TODO показывают где разумно вставлять соответствующие операции.
// Эти операции вы должны реализовать самостоятельно.

const static int TASK_MSG_KEY = 1234;     // ключ очереди заданий
const static int ANSWER_MSG_KEY = 1235;   // ключ очереди ответов
const static double EPS = 1.e-50;   // уровень проверки на 0 (для простоты)

struct MSGDATA   // содержательные данные сообщения, одинаковые для задания и для ответа
{                                                  
    long proc_id;  // идентификатор процесса
    long eqn_id;   // номер уравнения
    int  rcount;   // количество корней
    double r[3];   // коэффициенты (вход) или корни (выход, два первых элемента)
};

struct MSG 
{
    long type;      // тип: 1 – задание, 2 – ответ, 3 – конец работы
    MSGDATA data;   // данные
};

unsigned RandomTime()   // случайное время для задержки
{
    unsigned t = 1000000 + float(rand())/RAND_MAX * 1000000;
    //unsigned t = 10 + float(rand())/RAND_MAX * 10;
    return t;
}

// простейший решатель квадратного уравнения
// return - количество действительных корней

int Solver(double *coef, double *root)  // coef[3]  root[2]
{
    usleep(RandomTime());
    double a = coef[0], b = coef[1], c = coef[2];
    if (fabs(a) < EPS) return -1; // отказываемся решать не квадратные уравнения ! 
    double d = b * b - 4 * a * c;
    if (d < 0) return 0;
    b /= 2 * a;
    c /= a;
    d = sqrt(d) / (2 * a);
    if (b > 0) root[0] = -b - d;
    else       root[0] = -b + d;
    root[1] = c / root[0];
    return (fabs(root[0] - root[1]) < EPS) ? 1 : 2;
}

/*
распределение задач выполнено в формате читателей-писателей.

Writer считывает данные из файла и раздаёт задачи для SolverProcess в очереди задач.
SolverProcess принимает задачу, с помощью Solver решает её и отправляет ответ Reader в очередь ответов.
Reader принмает ответы и формирует итог в выходной файл.
*/

void SolverProcess(int id)  // id - идентификатор данного процесса
{
    int task_q = msgget(TASK_MSG_KEY, 0);
    int ans_q  = msgget(ANSWER_MSG_KEY, 0);
    if (task_q == -1 || ans_q == -1) {
        perror("msgget in child");
        exit(1);
    }

    while (true) {
        //printf("id == %d\n", id);
        MSG task;
        if (msgrcv(task_q, &task, sizeof(MSGDATA), 1, 0) == -1) {
            perror("msgrcv task");
            exit(1);
        }
        if (task.data.eqn_id == -1) break;

        //if (task.type == 3) break;

        double roots[2];
        int root_cnt = Solver(task.data.r, roots);

        MSG reply;
        reply.type = 2;
        reply.data.proc_id = id;
        reply.data.eqn_id = task.data.eqn_id;
        reply.data.rcount = root_cnt;
        if (root_cnt > 0) {
            reply.data.r[0] = roots[0];
            reply.data.r[1] = roots[1];
        }
        if (msgsnd(ans_q, &reply, sizeof(MSGDATA), 0) == -1) {
            perror("msgsnd answer");
            exit(1);
        }
    }
    exit(0);
}


void WriterProcess(int nproc, const char *infile) 
{
    FILE *fin = fopen(infile, "r");
    if (!fin) {
        perror("fopen in writer");
        exit(1);
    }

    int task_q = msgget(TASK_MSG_KEY, 0);
    int ans_q  = msgget(ANSWER_MSG_KEY, 0);
    if (task_q == -1 || ans_q == -1) {
        perror("msgget in writer");
        fclose(fin);
        exit(1);
    }

    long eqn_id;
    double a, b, c;
    while (fscanf(fin, "%ld %lf %lf %lf", &eqn_id, &a, &b, &c) == 4) {
        MSG task;
        task.type = 1;
        task.data.proc_id = 0;
        task.data.eqn_id = eqn_id;
        task.data.r[0] = a;
        task.data.r[1] = b;
        task.data.r[2] = c;
        if (msgsnd(task_q, &task, sizeof(MSGDATA), 0) == -1) {
            perror("msgsnd task");
            break;
        }
    }
    fclose(fin);
    
    // завершаем работу всех solver
    for (int i = 0; i < nproc; ++i) {
        MSG stop;
        stop.type = 1;
        stop.data.eqn_id = -1;
        if (msgsnd(task_q, &stop, sizeof(MSGDATA), 0) == -1) {
            perror("msgsnd stop");
        }
    }
    exit(0);
}


void ReaderProcess(int nproc, const char *outfile) 
{
    FILE *fout = fopen(outfile, "w");
    if (!fout) {
        perror("fopen in reader");
        exit(1);
    }

    int ans_q = msgget(ANSWER_MSG_KEY, 0);
    if (ans_q == -1) {
        perror("msgget in reader");
        fclose(fout);
        exit(1);
    }
    
    std::vector<int> stats(nproc, 0);

    int received = 0;
    int pid;
    while (true) {
        MSG msg;
        if (msgrcv(ans_q, &msg, sizeof(MSGDATA), 0, 0) == -1) {
            perror("msgrcv answer");
            break;
        }
        if (msg.type == 3) break;   // конец от писателя пришёл

        ++received;
        //printf("%d\n", received); 
        pid = msg.data.proc_id;
        if (pid >= 0 && pid < nproc) stats[pid]++;

        if (msg.data.rcount == -1) {
            fprintf(fout, "%ld %ld %10.4f %10.4f %10.4f не квадратное\n",
                    msg.data.proc_id, msg.data.eqn_id,
                    msg.data.r[0], msg.data.r[1], msg.data.r[2]);
        } else if (msg.data.rcount == 0) {
            fprintf(fout, "%ld %ld  нет корней\n",
                    msg.data.proc_id, msg.data.eqn_id);
        } else if (msg.data.rcount == 1) { // один корень
            fprintf(fout, "%ld %ld %10.4f  %10.4f\n",
                    msg.data.proc_id, msg.data.eqn_id,
                    msg.data.r[0], msg.data.r[0]);
        } else { // 2 корня
            fprintf(fout, "%ld %ld %10.4f %10.4f\n",
                    msg.data.proc_id, msg.data.eqn_id,
                    msg.data.r[0], msg.data.r[1]);
        }
    }

    fclose(fout);

    printf("\nСтатистика работы решателей:\n");
    for (int i = 0; i < nproc; ++i) {
        if (stats[i] > 0) {
            printf("Процесс %d решил %d уравнений\n", i, stats[i]);
        }
    }
    exit(0);
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
    const char *infile = argv[2];
    const char *outfile = argv[3];

    int task_q = msgget(TASK_MSG_KEY, IPC_CREAT | 0666);
    int ans_q  = msgget(ANSWER_MSG_KEY, IPC_CREAT | 0666);
    if (task_q == -1 || ans_q == -1) {
        perror("msgget");
        return -1;
    }

    printf("fork writer\n");
    pid_t writer = fork();
    if (writer == -1) {
        perror("fork writer");
        return -1;
    } else if (writer == 0) {
        WriterProcess(nproc, infile);
    }

    printf("fork reader\n");
    pid_t reader = fork();
    if (reader == -1) {
        perror("fork reader");
        return -1;
    } else if (reader == 0) {
        ReaderProcess(nproc, outfile);
    }

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


    waitpid(writer, NULL, 0);
    for (int i = 0; i < nproc; ++i) {
        wait(NULL);
    }

    // для читателя: заданий больше не будет
    MSG eof;
    eof.type = 3;
    if (msgsnd(ans_q, &eof, sizeof(MSGDATA), 0) == -1) {
        perror("msgsnd eof");
    }

    waitpid(reader, NULL, 0);
    msgctl(task_q, IPC_RMID, NULL);
    msgctl(ans_q, IPC_RMID, NULL);

    return 0;
}
