#include "sumnumbers.h"

double SumNumbers (FILE *f) {
    int last = 0, sum = 0, current = 0, boolean = 0;

    while(1) {
        fscanf(f, "%i", &current);
        if (feof(f)) {break;} // если дошли до конца файла
        if (current > last) { // проверка на возрастание
            if (current % 2 == 0) { // проверка на четность
                sum += current;
            }
            if (boolean && (last % 2 == 0)) {sum += last;} // если last > current, но current < next
            boolean = 0;
        }
        else {boolean = 1;}
        last = current;
    }
    return sum;
}