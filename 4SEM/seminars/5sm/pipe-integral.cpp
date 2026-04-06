#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

// для простоты, параметры интегрирования глобальные
static double a = 0.;   
static double b = 1.;   
static int n = 100000000; 
double f(double x) { return exp(x); }

// каналы
static int from_root[2];  // для запроса результата
static int to_root[2];    // для получения результата


// функция интегрирования методом трапеций
double integrate (double a, double b, int n)
{   
    double res;   // результат
    double h = (b - a) / n;;     // шаг интегрирования 

    res = 0.5*(f(a) + f(b));
    for (int i = 1; i < n; i++) {
        res += f (a + i*h);
    }
    res *= h;
    return res;
}

// функция интегрирования в рамках отдельного процесса
void process (int proc_id, int proc_total)
{
    printf("process %d of %d\n",proc_id, proc_total);

    // параметры интегрирования в данном процессе
    double len = (b - a) / proc_total;
    int proc_n = n / proc_total;
    double proc_a = a + proc_id * len;
    double proc_b = proc_a + len;
    double proc_res;

    // вычисления
    proc_res = integrate (proc_a,proc_b,proc_n);

    // ждем запроса на результат
    char byte;  // просто байт для сигнального сообщения
    if (read (from_root[0], &byte, 1) != 1) { 
        fprintf (stderr, "Read ERROR in process %d, pid = %d\n", proc_id, getpid());
        return;
    }
    // передаем результат главному процессу 
    if (write (to_root[1], &proc_res, sizeof(double)) != sizeof (double)) {
        fprintf (stderr, "Write ERROR in process %d, pid = %d\n", proc_id, getpid());
        return;
    }
}


int main ()
{
    //  количество процессов (для простоты - явно)
    int proc_total = 16;

    // результаты промежуточный и общий
    double res, integral = 0.;  
  
    // cоздаем каналы
    if (pipe (from_root) == -1 || pipe (to_root) == -1) {
        fprintf (stderr, "Cannot pipe\n");
        exit(0);
    }

    // запускаем процессы 
    for (int i = 0; i < proc_total ; i++)
    {
        pid_t pid = fork ();
        if (pid == -1) {
            fprintf (stderr, "Cannot fork!\n");
            exit(0);
        } else if (pid == 0) {
            // порожденный процесс 
            // закрываем ненужные направления обмена 
            close (from_root[1]);
            close (to_root[0]);

            // вызываем функцию процесса с нужными параметрами
            process(i, proc_total);

            // все сделали, можно все закрыть
            close (from_root[0]);
            close (to_root[1]);
            return 0;
        }
        // цикл продолжается в родительском процессе
    }
    // все процессы запущены, теперь разбираемся с результатами

    // закрываем не нужные pipe
    close (from_root[0]);
    close (to_root[1]);

    // получаем результаты 
    for (int i = 0; i < proc_total ; i++) {
        // посылаем запрос результата от процесса
        char byte = (char) i;
        if (write (from_root[1], &byte, 1) != 1) {
            fprintf (stderr, "Write ERROR in root\n");
            exit(0);
        }
        // читаем результат 
        if (read (to_root[0], &res, sizeof (double)) != sizeof (double)) {
            fprintf (stderr, "Read ERROR in root\n");
            exit(0);
        }
        integral += res;
    }
    // все порожденные процессы отработали
    // но все же подождем завершения на всякий случай
    while(wait(0) > 0);

    // Закрываем каналы 
    close (from_root[1]);
    close (to_root[0]);

    printf ("Integral from %lf to %lf = %.18lf\n", a, b, integral);
    return 0;
}



