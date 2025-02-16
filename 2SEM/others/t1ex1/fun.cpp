#include "t1ex1.h"

double Func1 (long long n) {
    double res = 0;
   for (int k = 1; k <= n; k++) {
        res = res + (1.0 / sqrt(k));
   }
   return res;
}


double Func1rev (long long n) {
    double res = 0;
   for (int k = n; k > 0; k--) {
        res = res + (1.0 / sqrt(k));
   }
   return res;
}


double Func2 (long long n) {
    double res = 0;
   for (int k = 1; k <= n; k++) {
        res = res + (log(k) / k);
   }
   return res;
}


double Func2rev (long long n) {
    double res = 0;
   for (int k = n; k > 0; k--) {
        res = res + (log(k) / k);
   }
   return res;
}


double Func3 (long long n) {
    double res = 0;
   for (int k = 1; k <= n; k++) {
        res = res + (1.0 / k);
   }
   return res;
}


double Func3rev (long long n) {
    double res = 0;
   for (int k = n; k > 0; k--) {
        res = res + (1.0 / k);
   }
   return res;
}


double Func4 (long long n) {
    double res = 0;
   for (int k = 1; k <= n; k++) {
        res = res + (1.0 / (k * k));
   }
   return res;
}


double Func4rev (long long n) {
    double res = 0;
   for (int k = n; k > 0; k--) {
        res = res + (1.0 / (k * k));
   }
   return res;
}

int Factorial(long long n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * Factorial(n - 1);
}

double Func5 (long long n) {
    double res = 0;
   for (int k = 1; k <= n; k++) {
        res = res + (1.0 / Factorial(k));
   }
   return res;
}


double Func5rev (long long n) {
    double res = 0;
   for (int k = n; k > 0; k--) {
        res = res + (1.0 / Factorial(k));
   }
   return res;
}