#include <stdio.h>
#include <math.h>

#define MAX_ITER 1000
#define EPS 1e-10
#define EPS2 1e-5
double f (double x);
double Deriv_f (double (*f)(double), double x);
double Newton (double x0, double (*f)(double), int *err);


double f (double x) {
    //return x * x - 2.0;
    return exp(x) - 2;
}



double Deriv_f (double (*f)(double), double x) {
    double h = EPS2;
    return (f(x + h) - f(x)) / (h);
}


double Newton (double x0, double (*f)(double), int *err) {
    double x_prev = x0;
    double x_curr = x0;
    double fx, dfx;
    int iter = 0;
    *err = 0;
    
    for (int i = 0; i < MAX_ITER; i++) {
        fx = f(x_curr);
        
        if (fabs(fx) < EPS) {
            iter = i;
            *err = 0;
            return x_curr;
        }
        
        dfx = Deriv_f(f, x_curr);
        
        if (fabs(dfx) < EPS) {
            iter = i;
            *err = 1; // Нулевая производная
            return x_curr;
        }
        
        x_prev = x_curr;
        x_curr = x_curr - fx / dfx;
        
        if (fabs(x_curr - x_prev) < EPS) {
            iter = i + 1;
            *err = 0;
            return x_curr;
        }
        
        if (fabs(x_curr) > 1e10 || !isfinite(x_curr)) {
            iter = i + 1;
            *err = 2; // Расходимость
            return x_curr;
        }
        
        (iter)++;
    }
    
    *err = 3;
    return x_curr;
}


int main(void) {
    double x = 1.0;
    int err = 0;
    
    double root = Newton(x, f, &err);

    if(err == 0) printf("ответ: %.20lf\n", root);
    else if(err == 1) {
        printf("нулевая производная\n");
        printf("ответ: %.20lf\n", root);
    }
    else if(err == 2) {
        printf("алгоритм разошёлся\n");
        printf("ответ: %.20lf\n", root);
    }
    else if(err == 3) printf("максимум по количеству итераций\n");
    
    return 0;
}